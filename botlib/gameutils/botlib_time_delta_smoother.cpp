#include <commonlib_exception.h>
#include <botlib_time_delta_smoother.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TimeDeltaSmoother::TimeDeltaSmoother()
    : timeDeltaSum_(0.0f)
    , totalSlots_(0)
    , lastSlot_(0)
    , curTimeDelta_(0.0f)
{
}

TimeDeltaSmoother::~TimeDeltaSmoother()
{
}

void TimeDeltaSmoother::init(unsigned int timeDeltaHistoryLen)
{
    if (timeDeltaHistoryLen == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid timeDeltaHistoryLen");
    }

    timeDeltaHistory_.resize(timeDeltaHistoryLen);
}

void TimeDeltaSmoother::start()
{
    for (auto it = timeDeltaHistory_.begin(); it != timeDeltaHistory_.end(); ++it)
    {
        *it = 0.0f;
    }

    prevTime_ = Clock::now();
    timeDeltaSum_ = 0.0f;
    totalSlots_ = 0;
    lastSlot_ = 0;
}

void TimeDeltaSmoother::updateTimeDelta()
{
    using namespace std::chrono;

    TimePoint curTime = Clock::now();
    duration<float> dur = curTime - prevTime_;
    float timeDelta = dur.count();

    unsigned int histSize = timeDeltaHistory_.size();

    if (totalSlots_ == histSize)
    {
        timeDeltaSum_ += timeDelta - timeDeltaHistory_[lastSlot_];
    }
    else
    {
        timeDeltaSum_ += timeDelta;
        totalSlots_++;
    }

    timeDeltaHistory_[lastSlot_] = timeDelta;
    lastSlot_ = (lastSlot_ + 1) % histSize;
    prevTime_ = curTime;

    curTimeDelta_ = timeDeltaSum_ / totalSlots_;
}

} // end of namespace botlib
} // end of namespace mcdane

