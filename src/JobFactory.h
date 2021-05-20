#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "Job.h"

class JobFactory {
private:
    static Job *createWalkerJob();

    static Job *createDiggerJob();

    static Job *createEscaperJob();

    static Job *createExploderJob();

    static Job *createMinerJob();

    static Job *createFloaterJob();

    static Job *createBasherJob();

    static Job *createBlockerJob();

    static Job *createFallerJob();

    static Job *createClimberJob();

    static Job *createBuilderJob();


public:

    static Job* createJob(Jobs jobToCreate);
};


#endif // _JOBFACTORY_INCLUDE

