#include <botlib_robot.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

Skill::Skill()
    : t_(nullptr)
    , robot_(nullptr)
    , enabled_(false)
{
}

Skill::Skill(const SkillTemplate* t,
             Robot* robot,
             bool enabled1)
{
    init(t, robot, enabled1);
}

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

void Skill::apply(UpdateContext& cxt)
{
    robot_->addEnergy(-t_->energyCost());
}

} // end of namespace botlib
} // end of namespace mcdane
