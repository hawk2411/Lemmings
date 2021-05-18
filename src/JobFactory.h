#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "Job.h"

class JobFactory {

public:

    static JobFactory &instance() {
        static JobFactory instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

    static Job* createJob(Jobs jobToCreate);
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
};


#endif // _JOBFACTORY_INCLUDE

