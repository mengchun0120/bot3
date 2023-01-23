#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_update_context.h>
#include <botlib_target_finder.h>
#include <botlib_targeted_blast_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetedBlastSkill::TargetedBlastSkill(const TargetedBlastSkillTemplate* t,
                                       Robot* robot)
{
    init(t, robot);
}

void TargetedBlastSkill::update(UpdateContext& cxt)
{
    timeSinceLastBlast_ = cxt.timeDelta();

    if (!available())
    {
        if (!getTemplate()->keepAlive())
        {
            setEnabled(false);
        }
        return;
    }

    Side enemySide = robot_->side() == Side::AI ? Side::PLAYER : Side::AI;
    TargetFinder finder = TargetFinder(enemySide, 1, cxt.
}

void TargetedBlastSkill::init(const TargetedBlastSkillTemplate* t,
                              Robot* robot)
{
    Skill::init(t, robot);
    timeSinceLastBlast_ = t_->coolDown();
}

} // end of namespace botlib
} // end of namespace mcdane
