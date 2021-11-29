#ifndef INCLUDED_BOTLIB_TIME_DELTA_SMOOTHER_H
#define INCLUDED_BOTLIB_TIME_DELTA_SMOOTHER_H

#include <vector>
#include <commonlib_time_utils.h>

namespace mcdane {
namespace botlib {

class TimeDeltaSmoother {
public:
    TimeDeltaSmoother();

    virtual ~TimeDeltaSmoother();

    void init(unsigned int timeDeltaHistoryLen);

    void start();

    float getTimeDelta();

private:
    std::vector<float> timeDeltaHistory_;
    float timeDeltaSum_;
    unsigned int totalSlots_;
    unsigned int lastSlot_;
    commonlib::TimePoint prevTime_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

