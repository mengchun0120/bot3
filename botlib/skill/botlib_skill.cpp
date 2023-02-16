#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_robot.h>
#include <botlib_progress_pie.h>
#include <botlib_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Skill::Skill()
    : t_(nullptr)
    , flags_(0)
    , robot_(nullptr)
{
}

Skill::Skill(const SkillTemplate* t,
             Robot* robot,
             bool enabled1)
{
    init(t, robot, enabled1);
}

Skill::~Skill()
{
}

void Skill::init(const SkillTemplate* t,
                 Robot* robot,
                 bool enabled1)
{
    t_ = t;
    flags_ = 0;
    robot_ = robot;
    setEnabled(enabled1);
}

} // end of namespace botlib
} // end of namespace mcdane
