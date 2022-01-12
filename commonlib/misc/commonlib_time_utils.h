#ifndef INCLUDED_COMMONLIB_TIME_UTILS_H
#define INCLUDED_COMMONLIB_TIME_UTILS_H

#include <chrono>

namespace mcdane {
namespace commonlib {

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

inline float timeDistMs(const TimePoint &startTime, const TimePoint &endTime)
{
    using namespace std::chrono;
    milliseconds dur = duration_cast<milliseconds>(endTime - startTime);
    return static_cast<float>(dur.count());
}

inline float elapsedTimeMs(const TimePoint &startTime)
{
    return timeDistMs(startTime, Clock::now());
}

inline float timeDistS(const TimePoint &startTime, const TimePoint &endTime)
{
    using namespace std::chrono;
    seconds dur = duration_cast<seconds>(endTime - startTime);
    return static_cast<float>(dur.count());
}

inline float elapsedTimeS(const TimePoint &startTime)
{
    return timeDistS(startTime, Clock::now());
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

