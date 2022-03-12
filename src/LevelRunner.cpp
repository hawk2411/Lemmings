#include "Game.h"
#include "StateManager.h"
#include "ParticleSystemManager.h"
#include "Utils.h"

#include "LevelRunner.h"
#include "IMaskManager.h"
#include "LevelIndex.h"

LevelRunner::LevelRunner(ShaderManager *shaderManager,
                         ParticleSystemManager *particleSystemManager, const LevelIndex &levelIndex)
        : _deadLemmings(0), _shaderManager(shaderManager),
          _particleSystemManager(particleSystemManager),
          _savedLemmings(0),
          _releaseRate(0),
          _availableLemmings(0),
          _levelIndex(levelIndex),
          _currentTime(0.0f),
          _lastTimeSpawnedLemming(0),
          _spawningLemmings(false),
          _finishedLevel(false),
          _exploding(false),
          music_(nullptr, Mix_FreeMusic),
          dooropenSound_(createSound("sounds/lemmingsEffects/Letsgo.ogg")),
          channel_(-1) {}

LevelRunner::~LevelRunner() = default;


void LevelRunner::changeLevel(const LevelIndex &levelIndex) {
    _levelIndex = levelIndex;
    _levelStartValues = std::make_unique<Level>(_shaderManager, _levelIndex.mode, _levelIndex.levelNo);

    _currentTime = 0.0f;

    clearLemmings();

    _releaseRate = _levelStartValues->releaseRate;
    _currentTime = 0.0f;
    _lastTimeSpawnedLemming = -3500;

    _availableLemmings = _levelStartValues->numLemmings;
    _spawningLemmings = true;

    _deadLemmings = 0;
    _savedLemmings = 0;

    _finishedLevel = false;
    _exploding = false;

    const string musicPath = "sounds/Lemming" + to_string(_levelIndex.levelNo) + ".ogg";
    music_ = createMusic(musicPath);
    channel_ = Mix_PlayChannel(-1, dooropenSound_.get(), 0);
    Mix_VolumeChunk(dooropenSound_.get(), MIX_MAX_VOLUME);
}

void LevelRunner::update(int deltaTime, IMaskManager *currentMask) {
    _currentTime += static_cast<float>(deltaTime);

    if (static_cast<int>(_currentTime / 1000 ) >= _levelStartValues->time) {
        finishLevel();
    }

    if (!_levelStartValues->_trapdoor->isOpened()) {
        _levelStartValues->_trapdoor->update(deltaTime);
        if (_levelStartValues->_trapdoor->isOpened() && channel_ != -1) {
            _currentTime = 0;
            Mix_HaltChannel(channel_);
            channel_ = -1;
            Mix_PlayMusic(music_.get(), -1);
            Mix_VolumeMusic(MIX_MAX_VOLUME);
        }
        return;
    }

    if (_spawningLemmings) {
        spawnLemmings();
    }
    updateLemmings(deltaTime, currentMask);

    _levelStartValues->_door->update(deltaTime);
    _levelStartValues->_trapdoor->update(deltaTime);

    if (_savedLemmings + _deadLemmings == _levelStartValues->numLemmings) {
        finishLevel();
    }
}

void LevelRunner::render() {
    _levelStartValues->_trapdoor->render(_levelStartValues->cameraPos);
    _levelStartValues->_door->render(_levelStartValues->cameraPos);
    renderLemmings();
}

bool LevelRunner::finished() const {
    return _finishedLevel;
}

void LevelRunner::spawnLemmings() {
    int elapsedTimeSinceLastLemming = static_cast<int>(_currentTime - static_cast<float>(_lastTimeSpawnedLemming));
    int timeToNextLemming = 3500 * (100 - _releaseRate) / 50;    //TODO what is that formula?

    if (elapsedTimeSinceLastLemming >= timeToNextLemming) {
        --_availableLemmings;
        _lastTimeSpawnedLemming = static_cast<int>(_currentTime);
        auto newLemming = std::make_unique<Lemming>(_levelStartValues->_trapdoor->getEnterPosition(),
                                                    _shaderManager, _particleSystemManager);
        newLemming->setWalkingRight(true);
        _lemmings.insert(std::move(newLemming));

    }

    _spawningLemmings = _availableLemmings != 0;
}

int LevelRunner::getNumLemmingsAlive() {
    return _lemmings.size();
}

int LevelRunner::getPercentageSavedLemmings() {
    return float(_savedLemmings) / _levelStartValues->numLemmings * 100;
}

int LevelRunner::getPercentageTotalLemmings() {
    return _levelStartValues->goalLemmings;
}

void LevelRunner::stopSpawningLemmings() {
    _spawningLemmings = false;
}

int LevelRunner::getCurrentTime() {
    return _currentTime / 1000;
}

int LevelRunner::getRemainingTime() {
    return _levelStartValues->time - getCurrentTime();
}


int LevelRunner::getActualLevel() const {
    return _levelIndex.levelNo;
}

LevelModes::Mode LevelRunner::getActualMode() const {
    return _levelIndex.mode;
}

void LevelRunner::apocalypse() {
    if (_exploding) {
        return;
    }

    _exploding = true;
    _spawningLemmings = false;
    _deadLemmings += _availableLemmings;

    for (auto &lemming : _lemmings) {
        lemming->writeDestiny(0);
    }
}


int LevelRunner::getReleaseRate() const {
    return _releaseRate;
}

int LevelRunner::getMinReleaseRate() const {
    return _levelStartValues->minReleaseRate;
}


void LevelRunner::decreaseReleaseRate() {
    _releaseRate = Utils::max(_levelStartValues->minReleaseRate, _releaseRate - 5);
}

void LevelRunner::increaseReleaseRate() {
    _releaseRate = Utils::min(99, _releaseRate + 5);
}

int LevelRunner::getLemmingIndexInPos(int posX, int posY) {
    int i = -1;
    std::set<Lemming *>::iterator it;
    for (const auto &lemming : _lemmings) {
        ++i;
        glm::vec2 lemmingPosition = lemming->getPosition();
        glm::vec2 lemmingSize = glm::vec2(16);
        if (Utils::insideRectangle(glm::vec2(posX, posY) + _levelStartValues->cameraPos,
                                   lemmingPosition, lemmingSize)) {
            return i;
        }
    }

    return -1;
}

string LevelRunner::getLemmingJobNameIndex(int index) {
    if (index == -1)
        return "";
    auto it = _lemmings.begin();
    std::advance(it, index);
    return it->get()->getJob()->getName();
}

bool LevelRunner::assignJob(int lemmingIndex, Jobs jobToAssign) {
    auto currentLemming = _lemmings.begin();
    std::advance(currentLemming, lemmingIndex);
    if(currentLemming == _lemmings.end()) {
        return false;
    }


    Jobs lemmingActualJob = currentLemming->get()->getJob()->getCurrentJob();
    if (jobToAssign == lemmingActualJob) {
        return false;
    }

    if (lemmingActualJob == Jobs::FALLER && jobToAssign != Jobs::FLOATER) {
        return false;
    }

    if (jobToAssign == Jobs::EXPLODER) {
        currentLemming->get()->writeDestiny(0);
    } else {
        currentLemming->get()->changeJob(jobToAssign);
    }
    return true;
}

void LevelRunner::finishLevel() {
    _finishedLevel = true;
}

void LevelRunner::updateLemmings(int deltaTime, IMaskManager *currentMask) {
    auto it = _lemmings.begin();
    while (it != _lemmings.end()) {
        auto current = it++;
        current->get()->update(deltaTime, getLevelAttributes(), currentMask);

        bool saved = current->get()->saved();
        bool dead = current->get()->dead();
        if (saved) {
            _lemmings.erase(current);
            ++_savedLemmings;
        } else if (dead) {
            _lemmings.erase(current);
            ++_deadLemmings;
        }
    }
}

void LevelRunner::renderLemmings() {
    for (auto &lemming: _lemmings) {
        lemming->render(_levelStartValues->cameraPos);
    }
}


int LevelRunner::getJobCount(int index) {
    return _levelStartValues->lemmingsProJob[index];
}

void LevelRunner::decreaseJobCount(int index) {
    --_levelStartValues->lemmingsProJob[index];
}


void LevelRunner::endMusic() {
    if (channel_ != -1) {
        Mix_HaltChannel(channel_);
        channel_ = -1;
    }
    Mix_HaltMusic();
}

void LevelRunner::clearLemmings() {
    _lemmings.clear();
}

