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

    void deleteJobToAssign();

    void offerJob(JobNames jobName);

    bool hasJobToAssign();


    Jobs getJobToAssign() const { return jobToAssign; };

    static int jobNameToIndex(JobNames jobName);

    JobNames getLastOfferedJob() const { return lastOfferedJob; }

    void setLastOfferedJob(JobNames newJobName) { lastOfferedJob = newJobName; }

private:


    Jobs jobToAssign = Jobs::UNKNOWN;
    JobNames lastOfferedJob = NONE;
};

#endif // _JOBASSIGNER_INCLUDE


