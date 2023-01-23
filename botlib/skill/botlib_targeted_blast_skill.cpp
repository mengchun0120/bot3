#include <botlib_update_context.h>
#include <botlib_targeted_blast_skill.h>

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


}

void TargetedBlastSkill::init(const TargetedBlastSkillTemplate* t,
                              Robot* robot)
{
    Skill::init(t, robot);
    timeSinceLastBlast_ = t_->coolDown();
}

} // end of namespace botlib
} // end of namespace mcdane
