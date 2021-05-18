#include "Game.h"
#include "StateManager.h"
#include "ParticleSystemManager.h"
#include "Utils.h"

#include "LevelRunner.h"

LevelRunner::LevelRunner() : _jobCount(nullptr),
                               _deadLemmings(0),
                               _savedLemmings(0),
                               _goalLemmingNum(0),
                               _releaseRate(0),
                               _minReleaseRate(0),
                               _availableLemmings(0),
                               _actualLevel(0),
                               _actualMode(0),
                               _goalTime(0),
                               _currentTime(0.0f),
                               _lastTimeSpawnedLemming(0),
                               _spawningLemmings(false),
                               _finishedLevel(false),
                               _exploding(false),
                               _door(nullptr),
                               _trapdoor(nullptr),
                               _music(nullptr),
                               _dooropen(nullptr) {


    _dooropen = make_unique<Sound>(Game::instance()->getSoundManager(), "sounds/lemmingsEffects/Letsgo.ogg", FMOD_DEFAULT | FMOD_UNIQUE);
}

LevelRunner::~LevelRunner() = default;


void LevelRunner::init(const string& levelMode, int levelNum) {
    _currentTime = 0.0f;

    string levelName = levelMode + "-" + to_string(levelNum);
    _actualLevel = levelNum;
    if (levelMode == "fun") _actualMode = FUN_MODE;
    if (levelMode == "tricky") _actualMode = TRICKY_MODE;
    if (levelMode == "taxing") _actualMode = TAXING_MODE;

    Level::currentLevel().createFromFile("levels/" + levelName + ".txt");
    Level::currentLevel().init();

    _jobCount = Level::currentLevel().getLevelAttributes()->jobCount;

    clearLemmings();

    _goalLemmingNum = Level::currentLevel().getLevelAttributes()->goalLemmings;
    _releaseRate = Level::currentLevel().getLevelAttributes()->releaseRate;
    _minReleaseRate = Level::currentLevel().getLevelAttributes()->minReleaseRate;

    _goalTime = Level::currentLevel().getLevelAttributes()->time;
    _currentTime = 0.0f;
    _lastTimeSpawnedLemming = -3500;

    _availableLemmings = Level::currentLevel().getLevelAttributes()->numLemmings;
    _spawningLemmings = true;

    _door = Level::currentLevel().getLevelAttributes()->_door.get();
    _trapdoor = Level::currentLevel().getLevelAttributes()->trapdoor;

    _deadLemmings = 0;
    _savedLemmings = 0;

    _finishedLevel = false;
    _exploding = false;

    string musicPath = "sounds/Lemming" + to_string(levelNum) + ".ogg";
    _music = make_unique<Sound>(Game::instance()->getSoundManager(), musicPath, FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);

    _dooropen->playSound();
    _dooropen->setVolume(1.0f);
}

void LevelRunner::update(int deltaTime) {
    _currentTime += deltaTime;

    if (_currentTime / 1000 >= _goalTime) {
        finishLevel();
    }

    if (!_trapdoor->isOpened()) {
        _trapdoor->update(deltaTime);
        if (_trapdoor->isOpened()) {
            _currentTime = 0;
            _dooropen->stopSound();
            _music->playSound();
            _music->setVolume(1.f);
        }
        return;
    }

    if (_spawningLemmings) {
        spawnLemmings();
    }
    updateLemmings(deltaTime);

    _door->update(deltaTime);
    _trapdoor->update(deltaTime);

    if (_savedLemmings + _deadLemmings == Level::currentLevel().getLevelAttributes()->numLemmings) {
        finishLevel();
    }
}

void LevelRunner::render() {
    Level::currentLevel().getLevelAttributes()->trapdoor->render();
    Level::currentLevel().getLevelAttributes()->_door->render();
    renderLemmings();
}

bool LevelRunner::finished() {
    return _finishedLevel;
}

void LevelRunner::spawnLemmings() {
    int elapsedTimeSinceLastLemming = _currentTime - _lastTimeSpawnedLemming;
    int timeToNextLemming = 3500 * (100 - _releaseRate) / 50;    //TODO what is that formula?

    if (elapsedTimeSinceLastLemming >= timeToNextLemming) {
        --_availableLemmings;
        _lastTimeSpawnedLemming = _currentTime;
        Lemming *newLemming = new Lemming(Level::currentLevel().getLevelAttributes()->trapdoor->getEnterPosition());
        newLemming->setWalkingRight(true);
        _lemmings.insert(newLemming);

    }

    _spawningLemmings = _availableLemmings != 0;
}

int LevelRunner::getNumLemmingsAlive() {
    return _lemmings.size();
}

int LevelRunner::getPercentageSavedLemmings() {
    return float(_savedLemmings) / Level::currentLevel().getLevelAttributes()->numLemmings * 100;
}

int LevelRunner::getPercentageTotalLemmings() {
    return _goalLemmingNum;
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


int LevelRunner::getActualLevel() {
    return _actualLevel;
}

int LevelRunner::getActualMode() {
    return _actualMode;
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


int LevelRunner::getReleaseRate() {
    return _releaseRate;
}

int LevelRunner::getMinReleaseRate() {
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
        if (Utils::insideRectangle(glm::vec2(posX, posY) + Level::currentLevel().getLevelAttributes()->cameraPos,
                                   lemmingPosition, lemmingSize)) {
            return i;
        }
    }

    return -1;
}

string LevelRunner::getLemmingJobNameIndex(int index) {
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

void LevelRunner::updateLemmings(int deltaTime) {
    auto it = _lemmings.begin();
    while (it != _lemmings.end()) {
        auto current = it++;
        Lemming *currentLemming = *current;
        currentLemming->update(deltaTime);

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
        currentLemming->render();
    }
}


int LevelRunner::getJobCount(int index) {
    return _jobCount[index];
}

void LevelRunner::decreaseJobCount(int index) {
    --_jobCount[index];
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
