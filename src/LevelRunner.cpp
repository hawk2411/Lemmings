#include "Game.h"
#include "StateManager.h"
#include "ParticleSystemManager.h"
#include "Utils.h"

#include "LevelRunner.h"
#include "IMaskManager.h"
#include "LevelIndex.h"

LevelRunner::LevelRunner(SoundManager *soundManager, ShaderManager *shaderManager, const LevelIndex &levelIndex)
        : _deadLemmings(0), _soundManager(soundManager), _shaderManager(shaderManager),
          _savedLemmings(0),
          _goalLemmingNum(0),
          _releaseRate(0),
          _minReleaseRate(0),
          _availableLemmings(0),
          _levelIndex(levelIndex),
          _goalTime(0),
          _currentTime(0.0f),
          _lastTimeSpawnedLemming(0),
          _spawningLemmings(false),
          _finishedLevel(false),
          _exploding(false) {

    _dooropenSound = make_unique<Sound>(_soundManager, "sounds/lemmingsEffects/Letsgo.ogg", FMOD_DEFAULT | FMOD_UNIQUE);
    changeLevel(_levelIndex);
}

LevelRunner::~LevelRunner() = default;


void LevelRunner::changeLevel(const LevelIndex &levelIndex) {
    _levelIndex = levelIndex;
    _levelStartValues = std::make_unique<Level>(_shaderManager, levelIndex.mode, levelIndex.levelNo);
    _currentTime = 0.0f;


    clearLemmings();

    _releaseRate = _levelStartValues->releaseRate;
    _minReleaseRate = _levelStartValues->minReleaseRate;

    _goalTime = _levelStartValues->time;
    _currentTime = 0.0f;
    _lastTimeSpawnedLemming = -3500;

    _availableLemmings = _levelStartValues->numLemmings;
    _spawningLemmings = true;

    _deadLemmings = 0;
    _savedLemmings = 0;

    _finishedLevel = false;
    _exploding = false;

    string musicPath = "sounds/Lemming" + to_string(_levelIndex.levelNo) + ".ogg";
    _music = make_unique<Sound>(_soundManager, musicPath, FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);

    _dooropenSound->playSound();
    _dooropenSound->setVolume(1.0f);
}

void LevelRunner::update(int deltaTime, IMaskManager *currentMask) {
    _currentTime += static_cast<float>(deltaTime);

    if (static_cast<int>(_currentTime / 1000 ) >= _goalTime) {
        finishLevel();
    }

    if (!_levelStartValues->_trapdoor->isOpened()) {
        _levelStartValues->_trapdoor->update(deltaTime);
        if (_levelStartValues->_trapdoor->isOpened()) {
            _currentTime = 0;
            _dooropenSound->stopSound();
            _music->playSound();
            _music->setVolume(1.f);
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
        auto *newLemming = new Lemming(_levelStartValues->_trapdoor->getEnterPosition(), _soundManager, _shaderManager);
        newLemming->setWalkingRight(true);
        _lemmings.insert(newLemming);

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
    return _goalTime - getCurrentTime();
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

    std::set<Lemming *>::iterator it;
    for (it = _lemmings.begin(); it != _lemmings.end(); ++it) {
        Lemming *currentLemming = *it;
        currentLemming->writeDestiny(0);
    }
}


int LevelRunner::getReleaseRate() const {
    return _releaseRate;
}

int LevelRunner::getMinReleaseRate() const {
    return _minReleaseRate;
}


void LevelRunner::decreaseReleaseRate() {
    _releaseRate = Utils::max(_minReleaseRate, _releaseRate - 5);
}

void LevelRunner::increaseReleaseRate() {
    _releaseRate = Utils::min(99, _releaseRate + 5);
}

int LevelRunner::getLemmingIndexInPos(int posX, int posY) {
    int i = -1;
    std::set<Lemming *>::iterator it;
    for (it = _lemmings.begin(); it != _lemmings.end(); ++it) {
        ++i;
        Lemming *currentLemming = *it;
        glm::vec2 lemmingPosition = currentLemming->getPosition();
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
    Lemming *currentLemming = *it;
    return currentLemming->getJob()->getName();
}

bool LevelRunner::assignJob(int lemmingIndex, Jobs jobToAssign) {
    auto it = _lemmings.begin();
    std::advance(it, lemmingIndex);
    Lemming *currentLemming = *it;

    Jobs lemmingActualJob = currentLemming->getJob()->getCurrentJob();
    if (jobToAssign == lemmingActualJob) {
        return false;
    }

    if (lemmingActualJob == Jobs::FALLER && jobToAssign != Jobs::FLOATER) {
        return false;
    }

    if (jobToAssign == Jobs::EXPLODER) {
        currentLemming->writeDestiny(0);
    } else {
        currentLemming->changeJob(jobToAssign);
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
        Lemming *currentLemming = *current;
        currentLemming->update(deltaTime, getLevelAttributes(), currentMask);

        bool saved = currentLemming->saved();
        bool dead = currentLemming->dead();

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
    std::set<Lemming *>::iterator it;
    for (it = _lemmings.begin(); it != _lemmings.end(); ++it) {
        Lemming *currentLemming = *it;
        currentLemming->render(_levelStartValues->cameraPos);
    }
}


int LevelRunner::getJobCount(int index) {
    return _levelStartValues->lemmingsProJob[index];
}

void LevelRunner::decreaseJobCount(int index) {
    --_levelStartValues->lemmingsProJob[index];
}


void LevelRunner::endMusic() {
    _music->stopSound();
}

void LevelRunner::clearLemmings() {
    for (auto *lemmming: _lemmings) {
        delete lemmming;
    }
    _lemmings.clear();
}
