#include "PredefinedWordFactory.h"
#include "UIAdapter.h"


void UIAdapter::changeJobName(Sprite *jobNameSprite, const string &jobName) {
    if (jobName == "WALKER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::WALKER);
    } else if (jobName == "MINER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::MINER);
    } else if (jobName == "FLOATER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::FLOATER);

    } else if (jobName == "FALLER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::FALLER);

    } else if (jobName == "DIGGER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::DIGGER);

    } else if (jobName == "CLIMBER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::CLIMBER);

    } else if (jobName == "BUILDER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::BUILDER);

    } else if (jobName == "BLOCKER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::BLOCKER);

    } else if (jobName == "BASHER") {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::BASHER);

    } else {
        jobNameSprite->changeAnimation(PredefinedWordFactory::JobNames::NONE);
    }

}
