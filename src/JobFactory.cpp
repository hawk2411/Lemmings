#include <iostream>
#include "JobFactory.h"
#include "Walker.h"
#include "Digger.h"
#include "Escaper.h"
#include "Exploder.h"
#include "Miner.h"
#include "Floater.h"
#include "Basher.h"
#include "Blocker.h"
#include "Faller.h"
#include "Climber.h"
#include "Builder.h"


Job *JobFactory::createWalkerJob() {
    return new Walker();
}

Job *JobFactory::createDiggerJob() {
    return new Digger();
}

Job *JobFactory::createEscaperJob() {
    return new Escaper();
    }

Job *JobFactory::createExploderJob( ParticleSystemManager* particleSystemManager) {
    return new Exploder(particleSystemManager);
    }

Job *JobFactory::createMinerJob() {
    return new Miner();
    }

Job *JobFactory::createFloaterJob() {
    return new Floater();
}

Job *JobFactory::createBasherJob() {
    return new Basher();
}

Job *JobFactory::createBlockerJob() {
    return new Blocker();
}

Job *JobFactory::createFallerJob() {
    return new Faller();
}

Job *JobFactory::createClimberJob() {
    return new Climber();
}

Job *JobFactory::createBuilderJob() {
    return new Builder();
}

Job *JobFactory::createJob(Jobs jobToCreate,  ParticleSystemManager* particleSystemManager) {
    switch(jobToCreate)
    {
        case Jobs::WALKER:
            return createWalkerJob();
        case Jobs::DIGGER:
            return createDiggerJob();
        case Jobs::ESCAPER:
            return createEscaperJob();
        case Jobs::EXPLODER:
            return createExploderJob(particleSystemManager);
        case Jobs::MINER:
            return createMinerJob();
        case Jobs::FLOATER:
            return createFloaterJob();
        case Jobs::BASHER:
            return createBasherJob();
        case Jobs::BLOCKER:
            return createBlockerJob();
        case Jobs::FALLER:
            return createFallerJob();
        case Jobs::CLIMBER:
            return createClimberJob();
        case Jobs::BUILDER:
            return createBuilderJob();
        default:
            return nullptr;
    }
    return nullptr;
}
