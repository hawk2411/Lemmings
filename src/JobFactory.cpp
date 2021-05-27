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


Job *JobFactory::createWalkerJob(SoundManager *soundManager) {
    return new Walker(soundManager);
}

Job *JobFactory::createDiggerJob(SoundManager *soundManager) {
    return new Digger(soundManager);
}

Job *JobFactory::createEscaperJob(SoundManager *soundManager) {
    return new Escaper(soundManager);
    }

Job *JobFactory::createExploderJob(SoundManager *soundManager, ParticleSystemManager* particleSystemManager) {
    return new Exploder(soundManager, particleSystemManager);
    }

Job *JobFactory::createMinerJob(SoundManager *soundManager) {
    return new Miner(soundManager);
    }

Job *JobFactory::createFloaterJob(SoundManager *soundManager) {
    return new Floater(soundManager);
}

Job *JobFactory::createBasherJob(SoundManager *soundManager) {
    return new Basher(soundManager);
}

Job *JobFactory::createBlockerJob(SoundManager *soundManager) {
    return new Blocker(soundManager);
}

Job *JobFactory::createFallerJob(SoundManager *soundManager) {
    return new Faller(soundManager);
}

Job *JobFactory::createClimberJob(SoundManager *soundManager) {
    return new Climber(soundManager);
}

Job *JobFactory::createBuilderJob(SoundManager *soundManager) {
    return new Builder(soundManager);
}

Job *JobFactory::createJob(Jobs jobToCreate, SoundManager *soundManager, ParticleSystemManager* particleSystemManager) {
    switch(jobToCreate)
    {
        case Jobs::WALKER:
            return createWalkerJob(soundManager);
        case Jobs::DIGGER:
            return createDiggerJob(soundManager);
        case Jobs::ESCAPER:
            return createEscaperJob(soundManager);
        case Jobs::EXPLODER:
            return createExploderJob(soundManager, particleSystemManager);
        case Jobs::MINER:
            return createMinerJob(soundManager);
        case Jobs::FLOATER:
            return createFloaterJob(soundManager);
        case Jobs::BASHER:
            return createBasherJob(soundManager);
        case Jobs::BLOCKER:
            return createBlockerJob(soundManager);
        case Jobs::FALLER:
            return createFallerJob(soundManager);
        case Jobs::CLIMBER:
            return createClimberJob(soundManager);
        case Jobs::BUILDER:
            return createBuilderJob(soundManager);
        default:
            return nullptr;
    }
    return nullptr;
}
