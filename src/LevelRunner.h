#ifndef _LEVEL_RUNNER_INCLUDE
#define _LEVEL_RUNNER_INCLUDE

#include <set>
#include "MusicFabric.hpp"
#include "Lemming.h"
#include "Level.h"
#include "Door.h"
#include "Trapdoor.h"
#include "LevelIndex.h"
#include "ParticleSystemManager.h"

class LevelRunner {

public:
    LevelRunner(ShaderManager *shaderManager, ParticleSystemManager *particleSystemManager, const LevelIndex &levelIndex);

    ~LevelRunner();


    void changeLevel(const LevelIndex &levelIndex);

    void update(int deltaTime, IMaskManager *currentMask);

    void render();

    bool finished() const;

    int getNumLemmingsAlive() const;

    int getPercentageSavedLemmings()const;

    int getPercentageTotalLemmings()const;

    void stopSpawningLemmings();

    bool assignJob(int lemmingIndex, Jobs jobToAssign);

    int getLemmingIndexInPos(int posX, int posY);

    string getLemmingJobNameIndex(int index);

    int getCurrentTime() const;

    int getRemainingTime();

    void apocalypse();

    int getReleaseRate() const;

    int getMinReleaseRate() const;

    void decreaseReleaseRate();

    void increaseReleaseRate();

    int getActualLevel() const;

    LevelModes::Mode getActualMode() const;

    int getJobCount(int index);

    void decreaseJobCount(int index);

    void endMusic();

    Level *getLevelAttributes() const { return _levelStartValues.get(); }

private:
    /*
     * functions
     */
    void spawnLemmings();

    void finishLevel();

    void updateLemmings(int deltaTime, IMaskManager *currentMask);

    void renderLemmings();


    void clearLemmings();

    /*
     * fields
     */
    std::unique_ptr<Level> _levelStartValues;


    set<std::unique_ptr<Lemming>> _lemmings;

    int _deadLemmings;
    int _savedLemmings;
    int _releaseRate;
    int _availableLemmings;

    LevelIndex _levelIndex;

    float _currentTime;
    int _lastTimeSpawnedLemming;

    bool _spawningLemmings;
    bool _finishedLevel;

    bool _exploding;
    ShaderManager *_shaderManager;
    ParticleSystemManager* _particleSystemManager;
    music_ptr_t _music;
    sound_ptr_t _dooropenSound;
    int _channel;
};

#endif // _LEVEL_RUNNER_INCLUDE