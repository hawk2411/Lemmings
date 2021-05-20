#ifndef _LEVEL_RUNNER_INCLUDE
#define _LEVEL_RUNNER_INCLUDE

#include <set>
#include "SoundManager.h"
#include "Lemming.h"
#include "Level.h"
#include "Door.h"
#include "Trapdoor.h"
#include "Sound.h"

class LevelRunner {

public:
    LevelRunner(SoundManager *soundManager, LevelModes::Mode levelMode, int levelNo);
    ~LevelRunner();


    void changeLevel(LevelModes::Mode levelMode, int levelNum);

    void update(int deltaTime);

    void render();

    bool finished() const;

    int getNumLemmingsAlive();

    int getPercentageSavedLemmings();

    int getPercentageTotalLemmings();

    void stopSpawningLemmings();

    bool assignJob(int lemmingIndex, Jobs jobToAssign);

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
    Level* getLevelAttributes()const{return _levelStartValues.get();}

private:
    void spawnLemmings();

    std::unique_ptr<Level> _levelStartValues;


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
    SoundManager *_soundManager;

    unique_ptr<Sound> _music;
    unique_ptr<Sound> _dooropenSound;


    void finishLevel();

    void updateLemmings(int deltaTime);

    void renderLemmings();


    void clearLemmings();
};

#endif // _LEVEL_RUNNER_INCLUDE