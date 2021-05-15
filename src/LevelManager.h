#ifndef _LEVELMANAGER_INCLUDE
#define _LEVELMANAGER_INCLUDE

#include <set>
#include "Lemming.h"
#include "Level.h"
#include "Door.h"
#include "Trapdoor.h"
#include "SoundManager.h"

class LevelManager {

public:
    static LevelManager &getInstance() {
        static LevelManager instance;
        return instance;
    };

    void init(string levelMode, int levelNum);

    void update(int deltaTime);

    void render();

    bool finished();

    int getNumLemmingsAlive();

    int getPercentageSavedLemmings();

    int getPercentageTotalLemmings();

    void stopSpawningLemmings();

    bool assignJob(int lemmingIndex, Job *jobToAssign);

    int getLemmingIndexInPos(int posX, int posY);

    string getLemmingJobNameIndex(int index);

    int getCurrentTime();

    int getRemainingTime();

    void apocalypse();

    int getReleaseRate();

    int getMinReleaseRate();

    void decreaseReleaseRate();

    void increaseReleaseRate();

    int getActualLevel();

    int getActualMode();

    int getJobCount(int index);

    void decreaseJobCount(int index);

    void endMusic();


private:
    void spawnLemmings();


    int *_jobCount;
    set<Lemming *> _lemmings;    //TODO why the fuck is this a set? Are they sorted?


    int _deadLemmings;
    int _savedLemmings;
    int _goalLemmingNum;
    int _releaseRate;
    int _minReleaseRate;
    int _availableLemmings;

    int _actualLevel;
    int _actualMode;

    int _goalTime;
    float _currentTime;
    int _lastTimeSpawnedLemming;

    bool _spawningLemmings;
    bool _finishedLevel;

    bool _exploding;

    Door *_door;
    Trapdoor *_trapdoor;

    FMOD::Sound *_music, *_dooropen;
    FMOD::Channel *_channel;

    void finishLevel();

    void updateLemmings(int deltaTime);

    void renderLemmings();


    void clearLemmings();
};

#endif // _LEVELMANAGER_INCLUDE