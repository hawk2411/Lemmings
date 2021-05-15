#ifndef _JOBASSIGNER_INCLUDE
#define _JOBASSIGNER_INCLUDE

#include "Job.h"

class JobAssigner {

public:
    enum JobNames {
        BASHER,
        BLOCKER,
        BOMBER,
        BUILDER,
        CLIMBER,
        DIGGER,
        FALLER,
        FLOATER,
        MINER,
        WALKER,
        NONE
    };


    static JobAssigner &getInstance() {
        static JobAssigner instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

    void deleteJobToAssign();

    void offerJob(JobNames jobName);

    bool hasJobToAssign();

    void assigJobLemming(int lemmingIndex);


private:
    void decreaseOfferedJobCount();

    int getJobCount(JobNames jobName);

    int jobNameToIndex(JobNames jobName);

    Jobs jobToAssign = Jobs::UNKNOWN;
    JobNames lastOfferedJob = NONE;
};

#endif // _JOBASSIGNER_INCLUDE


