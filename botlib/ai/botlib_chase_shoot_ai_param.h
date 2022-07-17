#ifndef INCLUDED_BOTLIB_CHASE_SHOOT_AI_PARAM_H
#define INCLUDED_BOTLIB_CHASE_SHOOT_AI_PARAM_H

#include <rapidjson/document.h>

namespace mcdane {
namespace botlib {

class ChaseShootAIParam {
public:
    ChaseShootAIParam() = default;

    void init(const rapidjson::Value& v);

    inline float chaseDuration() const;

    inline float directionChangeInterval() const;

    inline float shootDuration() const;

    inline float chaseProb() const;

    inline float stopChaseDist() const;

private:
    float chaseDuration_;
    float directionChangeInterval_;
    float shootDuration_;
    float chaseProb_;
    float stopChaseDist_;
};

float ChaseShootAIParam::chaseDuration() const
{
    return chaseDuration_;
}

float ChaseShootAIParam::directionChangeInterval() const
{
    return directionChangeInterval_;
}

float ChaseShootAIParam::shootDuration() const
{
    return shootDuration_;
}

float ChaseShootAIParam::chaseProb() const
{
    return chaseProb_;
}

float ChaseShootAIParam::stopChaseDist() const
{
    return stopChaseDist_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

