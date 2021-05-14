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
    Walker *walkerJob = new Walker();
    return walkerJob;
}

Job *JobFactory::createDiggerJob() {
    Digger *diggerJob = new Digger();
    return diggerJob;
}

Job *JobFactory::createEscaperJob() {
    Escaper *escaperJob = new Escaper();
    return escaperJob;
}

Job *JobFactory::createExploderJob() {
    Exploder *exploderJob = new Exploder();
    return exploderJob;
}

Job *JobFactory::createMinerJob() {
    Miner *minerJob = new Miner();
    return minerJob;
}

Job *JobFactory::createFloaterJob() {
    Floater *floaterJob = new Floater();
    return floaterJob;
}

Job *JobFactory::createBasherJob() {
    Basher *basherJob = new Basher();
    return basherJob;
}

Job *JobFactory::createBlockerJob() {
    Blocker *blockerJob = new Blocker();
    return blockerJob;
}

Job *JobFactory::createFallerJob() {
    Faller *fallerJob = new Faller();
    return fallerJob;
}

Job *JobFactory::createClimberJob() {
    Climber *climberJob = new Climber();
    return climberJob;
}

Job *JobFactory::createBuilderJob() {
    Builder *builderJob = new Builder();
    return builderJob;
}

Job *JobFactory::createJob(Jobs jobToCreate) {
    switch(jobToCreate)
    {
        case Jobs::WALKER:
            return createWalkerJob();
        case Jobs::DIGGER:
            return createDiggerJob();
        case Jobs::FINISHER:
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
