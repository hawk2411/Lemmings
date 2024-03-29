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
          _music(nullptr, Mix_FreeMusic),
          _dooropenSound(createSound("sounds/lemmingsEffects/Letsgo.ogg")),
          _channel(-1) {}

LevelRunner::~LevelRunner() = default;


void LevelRunner::changeLevel(const LevelIndex &levelIndex) {
    _levelIndex = levelIndex;
    _levelStartValues = std::make_unique<Level>(_shaderManager, _levelIndex.mode, _levelIndex.levelNo);

    _currentTime = 0.0f;

    clearLemmings();

    _releaseRate = _levelStartValues->_releaseRate;
    _currentTime = 0.0f;
    _lastTimeSpawnedLemming = -3500;

    _availableLemmings = _levelStartValues->_numLemmings;
    _spawningLemmings = true;

    _deadLemmings = 0;
    _savedLemmings = 0;

    _finishedLevel = false;
    _exploding = false;

    const string musicPath = "sounds/Lemming" + to_string(_levelIndex.levelNo) + ".ogg";
    _music = createMusic(musicPath);
    _channel = Mix_PlayChannel(-1, _dooropenSound.get(), 0);
    Mix_VolumeChunk(_dooropenSound.get(), MIX_MAX_VOLUME);
}

void LevelRunner::update(int deltaTime, IMaskManager *currentMask) {
    _currentTime += static_cast<float>(deltaTime);

    if (static_cast<int>(_currentTime / 1000 ) >= _levelStartValues->_time) {
        finishLevel();
    }

    if (!_levelStartValues->_trapdoor->isOpened()) {
        _levelStartValues->_trapdoor->update(deltaTime);
        if (_levelStartValues->_trapdoor->isOpened() && _channel != -1) {
            _currentTime = 0;
            Mix_HaltChannel(_channel);
            _channel = -1;
            Mix_PlayMusic(_music.get(), -1);
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

    if (_savedLemmings + _deadLemmings == _levelStartValues->_numLemmings) {
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

int LevelRunner::getNumLemmingsAlive() const {
    return static_cast<int>(_lemmings.size());
}

int LevelRunner::getPercentageSavedLemmings()const {
    return _savedLemmings / _levelStartValues->_numLemmings * 100;
}

int LevelRunner::getPercentageTotalLemmings()const {
    return _levelStartValues->_goalLemmings;
}

void LevelRunner::stopSpawningLemmings() {
    _spawningLemmings = false;
}

int LevelRunner::getCurrentTime() const {
    return static_cast<int>(_currentTime / 1000.0);
}

int LevelRunner::getRemainingTime() {
    return _levelStartValues->_time - getCurrentTime();
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
    return _levelStartValues->_minReleaseRate;
}


void LevelRunner::decreaseReleaseRate() {
    _releaseRate = Utils::max(_levelStartValues->_minReleaseRate, _releaseRate - 5);
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
    return _levelStartValues->_lemmingsProJob[index];
}

void LevelRunner::decreaseJobCount(int index) {
    --_levelStartValues->_lemmingsProJob[index];
}


void LevelRunner::endMusic() {
    if (_channel != -1) {
        Mix_HaltChannel(_channel);
        _channel = -1;
    }
    Mix_HaltMusic();
}

void LevelRunner::clearLemmings() {
    _lemmings.clear();
}

