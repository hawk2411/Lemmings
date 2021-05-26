#ifndef _LEVEL_RUNNER_INCLUDE
#define _LEVEL_RUNNER_INCLUDE

#include <set>
#include "SoundManager.h"
#include "Lemming.h"
#include "Level.h"
#include "Door.h"
#include "Trapdoor.h"
#include "Sound.h"
//#include "IMaskManager.h"
#include "LevelIndex.h"

class LevelRunner {

public:
    LevelRunner(SoundManager *soundManager, ShaderManager * shaderManager, const LevelIndex& levelIndex);
    ~LevelRunner();


    void changeLevel(const LevelIndex &levelIndex);

    void update(int deltaTime, IMaskManager *currentMask);

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

    int getReleaseRate() const;

    int getMinReleaseRate() const;

    void decreaseReleaseRate();

    void increaseReleaseRate();

    int getActualLevel() const;

    LevelModes::Mode getActualMode()const;

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

    LevelIndex _levelIndex;

    int _goalTime;
    float _currentTime;
    int _lastTimeSpawnedLemming;

    bool _spawningLemmings;
    bool _finishedLevel;

    bool _exploding;
    SoundManager *_soundManager;
    ShaderManager *_shaderManager;

    unique_ptr<Sound> _music;
    unique_ptr<Sound> _dooropenSound;


    void finishLevel();

    void updateLemmings(int deltaTime, IMaskManager *currentMask);

    void renderLemmings();


    void clearLemmings();
};

#endif // _LEVEL_RUNNER_INCLUDE