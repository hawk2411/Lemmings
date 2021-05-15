#include "LevelManager.h"
#include "Game.h"
#include "StateManager.h"
#include "ParticleSystemManager.h"
#include "Utils.h"

void LevelManager::init(string levelMode, int levelNum) {
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
    _music = Game::instance().getSoundManager()->loadSound(musicPath, FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
    _dooropen = Game::instance().getSoundManager()->loadSound("sounds/lemmingsEffects/Letsgo.ogg", FMOD_DEFAULT | FMOD_UNIQUE);

    _channel = Game::instance().getSoundManager()->playSound(_dooropen);
    _channel->setVolume(1.);
}

void LevelManager::update(int deltaTime) {
    _currentTime += deltaTime;

    if (_currentTime / 1000 >= _goalTime) {
        finishLevel();
    }

    if (!_trapdoor->isOpened()) {
        _trapdoor->update(deltaTime);
        if (_trapdoor->isOpened()) {
            _currentTime = 0;
            _channel = Game::instance().getSoundManager()->playSound(_music);
            _channel->setVolume(1.f);
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

void LevelManager::render() {
    Level::currentLevel().getLevelAttributes()->trapdoor->render();
    Level::currentLevel().getLevelAttributes()->_door->render();
    renderLemmings();
}

bool LevelManager::finished() {
    return _finishedLevel;
}

void LevelManager::spawnLemmings() {
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

int LevelManager::getNumLemmingsAlive() {
    return _lemmings.size();
}

int LevelManager::getPercentageSavedLemmings() {
    return float(_savedLemmings) / Level::currentLevel().getLevelAttributes()->numLemmings * 100;
}

int LevelManager::getPercentageTotalLemmings() {
    return _goalLemmingNum;
}

void LevelManager::stopSpawningLemmings() {
    _spawningLemmings = false;
}

int LevelManager::getCurrentTime() {
    return _currentTime / 1000;
}

int LevelManager::getRemainingTime() {
    return _goalTime - getCurrentTime();
}


int LevelManager::getActualLevel() {
    return _actualLevel;
}

int LevelManager::getActualMode() {
    return _actualMode;
}

void LevelManager::apocalypse() {
    if (_exploding) {
        return;
    }

    _exploding = true;
    _spawningLemmings = false;
    _deadLemmings += _availableLemmings;

    std::set<Lemming *>::iterator it;
    for (it = _lemmings.begin(); it != _lemmings.end(); ++it) {
        Lemming *currentLemming = *it;
        currentLemming->writeDestiny();
    }
}


int LevelManager::getReleaseRate() {
    return _releaseRate;
}

int LevelManager::getMinReleaseRate() {
    return _minReleaseRate;
}


void LevelManager::decreaseReleaseRate() {
    _releaseRate = Utils::max(_minReleaseRate, _releaseRate - 5);
}

void LevelManager::increaseReleaseRate() {
    _releaseRate = Utils::min(99, _releaseRate + 5);
}

int LevelManager::getLemmingIndexInPos(int posX, int posY) {
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

string LevelManager::getLemmingJobNameIndex(int index) {
    auto it = _lemmings.begin();
    std::advance(it, index);
    Lemming *currentLemming = *it;
    return currentLemming->getJob()->getName();
}

bool LevelManager::assignJob(int lemmingIndex, Job *jobToAssign) {
    auto it = _lemmings.begin();
    std::advance(it, lemmingIndex);
    Lemming *currentLemming = *it;

    string lemmingActualJob = currentLemming->getJob()->getName();
    string jobToAssignName = jobToAssign->getName();

    if (jobToAssignName == lemmingActualJob) {
        return false;
    }

    if (lemmingActualJob == "FALLER" && jobToAssignName != "FLOATER") {
        return false;
    }

    if (jobToAssignName == "BOMBER") {
        currentLemming->writeDestiny();
    } else {
        currentLemming->changeJob(jobToAssign);
    }
    return true;
}

void LevelManager::finishLevel() {
    _finishedLevel = true;
}

void LevelManager::updateLemmings(int deltaTime) {
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

void LevelManager::renderLemmings() {
    std::set<Lemming *>::iterator it;
    for (it = _lemmings.begin(); it != _lemmings.end(); ++it) {
        Lemming *currentLemming = *it;
        currentLemming->render();
    }
}


int LevelManager::getJobCount(int index) {
    return _jobCount[index];
}

void LevelManager::decreaseJobCount(int index) {
    --_jobCount[index];
}


void LevelManager::endMusic() {
    _channel->stop();
}

void LevelManager::clearLemmings() {
    for(auto* lemmming: _lemmings) {
        delete lemmming;
    }
    _lemmings.clear();
}
