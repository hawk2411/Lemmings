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
    return new Walker(Jobs::WALKER);
}

Job *JobFactory::createDiggerJob() {
    return new Digger(Jobs::DIGGER);
}

Job *JobFactory::createEscaperJob() {
    return new Escaper(Jobs::ESCAPER);
    }

Job *JobFactory::createExploderJob() {
    return new Exploder(Jobs::EXPLODER);
    }

Job *JobFactory::createMinerJob() {
    return new Miner(Jobs::MINER);
    }

Job *JobFactory::createFloaterJob() {
    return new Floater(Jobs::FLOATER);
}

Job *JobFactory::createBasherJob() {
    return new Basher(Jobs::BASHER);
}

Job *JobFactory::createBlockerJob() {
    return new Blocker(Jobs::BLOCKER);
}

Job *JobFactory::createFallerJob() {
    return new Faller(Jobs::FALLER);
}

Job *JobFactory::createClimberJob() {
    return new Climber(Jobs::CLIMBER);
}

Job *JobFactory::createBuilderJob() {
    return new Builder(Jobs::BUILDER);
}

Job *JobFactory::createJob(Jobs jobToCreate) {
    switch(jobToCreate)
    {
        case Jobs::WALKER:
            return createWalkerJob();
        case Jobs::DIGGER:
            return createDiggerJob();
        case Jobs::ESCAPER:
            return createEscaperJob();
        case Jobs::EXPLODER:
            return createExploderJob();
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
