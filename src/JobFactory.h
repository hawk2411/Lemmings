#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "ParticleSystemManager.h"
#include "Job.h"

class JobFactory {
private:
    static std::unique_ptr<Job> createWalkerJob();

    static std::unique_ptr<Job> createDiggerJob();

    static std::unique_ptr<Job> createEscaperJob();

    static std::unique_ptr<Job> createExploderJob(ParticleSystemManager* particleSystemManager);

    static std::unique_ptr<Job> createMinerJob();

    static std::unique_ptr<Job> createFloaterJob();

    static std::unique_ptr<Job> createBasherJob();

    static std::unique_ptr<Job> createBlockerJob();

    static std::unique_ptr<Job> createFallerJob();

    static std::unique_ptr<Job> createClimberJob();

    static std::unique_ptr<Job> createBuilderJob();


public:

    static std::unique_ptr<Job> createJob(Jobs jobToCreate, ParticleSystemManager* particleSystemManager);
};


#endif // _JOBFACTORY_INCLUDE

