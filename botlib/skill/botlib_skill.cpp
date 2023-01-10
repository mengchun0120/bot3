#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

void Skill::init(const SkillTemplate* t,
                 Robot* robot,
                 bool enabled1)
{
    t_ = t;
    robot_ = robot;
    enabled_ = enabled1;
}

void Skill::setEnabled(bool enabled1)
{
    enabled_ = enabled1;
}

} // end of namespace botlib
} // end of namespace mcdane
