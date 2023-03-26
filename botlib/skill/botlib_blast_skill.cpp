#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_missile.h>
#include <botlib_blast_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BlastSkill::BlastSkill(const BlastSkillTemplate *t,
                       Robot *robot,
                       bool enabled1,
                       const Vector2 *buttonPos)
{
    init(t, robot, enabled1, buttonPos);
}

void BlastSkill::init(const BlastSkillTemplate *t,
                      Robot *robot,
                      bool enabled1,
                      const Vector2 *buttonPos)
{
    SkillWithCost::init(t, robot, enabled1, buttonPos);
}

bool BlastSkill::apply(UpdateContext &cxt)
{
    GameMap &map = *(cxt.map());
    auto &firePoints = getTemplate()->firePoints();
    auto &fireDirections = getTemplate()->fireDirections();
    const MissileTemplate *t = robot_->getTemplate()->missileTemplate();
    int sz = static_cast<int>(firePoints.size());

    for (int i = 0; i < sz; ++i)
    {
        Vector2 pos = robot_->pos() + firePoints[i];
        Missile *missile = cxt.factory().createMissile(t, robot_->side(),
                                                       pos, fireDirections[i]);
        map.addObj(missile);
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
