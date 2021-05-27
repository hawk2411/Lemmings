#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "ParticleSystemManager.h"
#include "Job.h"
#include "SoundManager.h"

class JobFactory {
private:
    static Job *createWalkerJob(SoundManager *soundManager);

    static Job *createDiggerJob(SoundManager *soundManager);

    static Job *createEscaperJob(SoundManager *soundManager);

    static Job *createExploderJob(SoundManager *soundManager, ParticleSystemManager* particleSystemManager);

    static Job *createMinerJob(SoundManager *soundManager);

    static Job *createFloaterJob(SoundManager *soundManager);

    static Job *createBasherJob(SoundManager *soundManager);

    static Job *createBlockerJob(SoundManager *soundManager);

    static Job *createFallerJob(SoundManager *soundManager);

    static Job *createClimberJob(SoundManager *soundManager);

    static Job *createBuilderJob(SoundManager *soundManager);


public:

    static Job *createJob(Jobs jobToCreate, SoundManager *soundManager, ParticleSystemManager* particleSystemManager);
};


#endif // _JOBFACTORY_INCLUDE

