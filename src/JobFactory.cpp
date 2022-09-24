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


std::unique_ptr<Job> JobFactory::createWalkerJob() {
    return std::make_unique<Walker>();
}

std::unique_ptr<Job> JobFactory::createDiggerJob() {
    return std::make_unique<Digger>();
}

std::unique_ptr<Job> JobFactory::createEscaperJob() {
    return std::make_unique<Escaper>();
    }

std::unique_ptr<Job> JobFactory::createExploderJob(ParticleSystemManager* particleSystemManager) {
    return std::make_unique<Exploder>(particleSystemManager);
    }

std::unique_ptr<Job> JobFactory::createMinerJob() {
    return std::make_unique<Miner>();
    }

std::unique_ptr<Job> JobFactory::createFloaterJob() {
    return std::make_unique<Floater>();
}

std::unique_ptr<Job> JobFactory::createBasherJob() {
    return std::make_unique<Basher>();
}

std::unique_ptr<Job> JobFactory::createBlockerJob() {
    return std::make_unique<Blocker>();
}

std::unique_ptr<Job> JobFactory::createFallerJob() {
    return std::make_unique<Faller>();
}

std::unique_ptr<Job> JobFactory::createClimberJob() {
    return std::make_unique<Climber>();
}

std::unique_ptr<Job> JobFactory::createBuilderJob() {
    return std::make_unique<Builder>();
}

std::unique_ptr<Job> JobFactory::createJob(Jobs jobToCreate, ParticleSystemManager* particleSystemManager) {
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
}
