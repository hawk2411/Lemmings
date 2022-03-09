#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "ParticleSystemManager.h"
#include "Job.h"

class JobFactory {
private:
    static Job *createWalkerJob();

    static Job *createDiggerJob();

    static Job *createEscaperJob();

    static Job *createExploderJob(ParticleSystemManager* particleSystemManager);

    static Job *createMinerJob();

    static Job *createFloaterJob();

    static Job *createBasherJob();

    static Job *createBlockerJob();

    static Job *createFallerJob();

    static Job *createClimberJob();

    static Job *createBuilderJob();


public:

    static Job *createJob(Jobs jobToCreate, ParticleSystemManager* particleSystemManager);
};


#endif // _JOBFACTORY_INCLUDE

