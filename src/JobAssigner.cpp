#include "JobAssigner.h"
#include "JobFactory.h"
#include "Scene.h"
#include "LevelRunner.h"

void JobAssigner::deleteJobToAssign() {
    jobToAssign = Jobs::UNKNOWN;
    lastOfferedJob = NONE;
}

void JobAssigner::offerJob(JobNames jobName) {

    deleteJobToAssign();

    switch (jobName) {
        case JobAssigner::BASHER:
            jobToAssign = Jobs::BASHER;
            break;
        case JobAssigner::BLOCKER:
            jobToAssign = Jobs::BLOCKER;
            break;
        case JobAssigner::BOMBER:
            jobToAssign = Jobs::EXPLODER;
            break;
        case JobAssigner::BUILDER:
            jobToAssign = Jobs::BUILDER;
            break;
        case JobAssigner::CLIMBER:
            jobToAssign = Jobs::CLIMBER;
            break;
        case JobAssigner::DIGGER:
            jobToAssign = Jobs::DIGGER;
            break;
        case JobAssigner::FALLER:
            jobToAssign = Jobs::FALLER;
            break;
        case JobAssigner::FLOATER:
            jobToAssign = Jobs::FLOATER;
            break;
        case JobAssigner::MINER:
            jobToAssign = Jobs::MINER;
            break;
        case JobAssigner::WALKER:
            jobToAssign = Jobs::WALKER;
            break;
        default:
            break;
    }

    lastOfferedJob = jobName;
}

bool JobAssigner::hasJobToAssign() {
    return lastOfferedJob != NONE;
}

void JobAssigner::assigJobLemming(int lemmingIndex) {
    if (lemmingIndex != -1) {
        if (LevelRunner::getInstance().assignJob(lemmingIndex, jobToAssign)) {
            jobToAssign = Jobs::UNKNOWN;

            decreaseOfferedJobCount();

            if (getJobCount(lastOfferedJob) > 0) {
                offerJob(lastOfferedJob);
            } else {
                lastOfferedJob = NONE;

            }
        }
    }
}

void JobAssigner::decreaseOfferedJobCount() {

    LevelRunner::getInstance().decreaseJobCount(jobNameToIndex(lastOfferedJob));

}

int JobAssigner::getJobCount(JobNames jobName) {
    return LevelRunner::getInstance().getJobCount(jobNameToIndex(lastOfferedJob));
}

int JobAssigner::jobNameToIndex(JobNames jobName) {
    int index;
    switch (jobName) {
        case JobAssigner::BASHER:
            index = 5;
            break;
        case JobAssigner::BLOCKER:
            index = 3;
            break;
        case JobAssigner::BOMBER:
            index = 2;
            break;
        case JobAssigner::BUILDER:
            index = 4;
            break;
        case JobAssigner::CLIMBER:
            index = 0;
            break;
        case JobAssigner::DIGGER:
            index = 7;
            break;
        case JobAssigner::FLOATER:
            index = 1;
            break;
        case JobAssigner::MINER:
            index = 6;
            break;
        case JobAssigner::NONE:
            index = -1;
            break;
    }

    return index;
}