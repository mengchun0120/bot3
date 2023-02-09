#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_target_finder.h>
#include <botlib_missile.h>
#include <botlib_targeted_blast_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetedBlastSkill::TargetedBlastSkill(const TargetedBlastSkillTemplate* t,
                                       Robot* robot,
                                       bool enabled1)
{
    init(t, robot, enabled1);
}

void TargetedBlastSkill::init(const TargetedBlastSkillTemplate* t,
                              Robot* robot,
                              bool enabled1)
{
    SkillWithCost::init(t, robot, enabled1);
}

bool TargetedBlastSkill::apply(UpdateContext& cxt)
{
    GameObjItemList targets(cxt.itemPool().deleter());
    findTargets(targets, cxt);
    if (targets.empty())
    {
        return false;
    }

    shootTargets(targets, cxt);

    return true;
}

commonlib::Region<int> TargetedBlastSkill::searchRegion(GameMap* map)
{
    float searchRange = getTemplate()->searchRange();
    const Vector2& p = robot_->pos();
    Region<float> r(p[0] - searchRange, p[0] + searchRange,
                    p[1] - searchRange, p[1] + searchRange);
    return map->getCoverArea(r);
}

void TargetedBlastSkill::findTargets(GameObjItemList& targets,
                                     UpdateContext& cxt)
{
    Side enemySide = robot_->side() == Side::AI ? Side::PLAYER : Side::AI;
    Region<int> area = searchRegion(cxt.map());
    TargetFinder finder(enemySide, getTemplate()->numTargets(),
                        targets, cxt.itemPool());

    cxt.map()->traverse(area, finder, GameMap::LAYER_ROBOT, 1);
    finder.getTargets();
}

void TargetedBlastSkill::shootTargets(GameObjItemList& targets,
                                      UpdateContext& cxt)
{
    const MissileTemplate* missileTemplate = getTemplate()->missileTemplate();
    float radius = getTemplate()->startRadius();
    GameMap& map = *(cxt.map());

    for (GameObjectItem* i = targets.first(); i; i = i->next())
    {
        Vector2 direction = normalize(i->item()->pos() - robot_->pos());
        Vector2 pos = direction * radius + robot_->pos();
        Missile* missile =
            cxt.factory().createMissile(missileTemplate, robot_->side(),
                                        pos, direction);
        map.addObj(missile);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
