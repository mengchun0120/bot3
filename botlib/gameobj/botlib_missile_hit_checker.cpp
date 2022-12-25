#include <commonlib_collide.h>
#include <botlib_context.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_tile.h>
#include <botlib_ai_robot.h>
#include <botlib_goodie.h>
#include <botlib_missile_hit_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MissileHitChecker::MissileHitChecker(UpdateContext& cxt,
                                     Missile& missile,
                                     bool inflictDamage)
    : cxt_(cxt)
    , missile_(missile)
    , inflictDamage_(inflictDamage)
    , collide_(false)
{
}


bool MissileHitChecker::operator()(GameObject* obj)
{
    if (!check(obj))
    {
        return true;
    }

    bool collide1 = checkRectCollideRect(missile_.collideRegion(),
                                         obj->collideRegion());
    if (!collide1)
    {
        return true;
    }

    collide_ = true;

    if (inflictDamage_)
    {
        doDamage(obj);
        return true;
    }

    return false;
}

void MissileHitChecker::doDamage(GameObject* obj)
{
    GameMap& map = *(cxt_.map());
    GameObjectDumper& dumper = cxt_.dumper();

    if (obj->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(obj);
        robot->doDamage(missile_.damage(), cxt_);

        if (robot->state() != GameObjectState::ALIVE && robot->side() == Side::AI)
        {
            generateGoodie(static_cast<AIRobot*>(robot));
        }

        if (robot->canBeDumped(map))
        {
            dumper.add(robot);
        }
    }
    else if (obj->type() == GameObjectType::TILE)
    {
        Tile* tile = static_cast<Tile*>(obj);
        tile->doDamage(missile_.damage());

        if (tile->canBeDumped(map))
        {
            dumper.add(tile);
        }
    }
}

void MissileHitChecker::generateGoodie(AIRobot* robot)
{
    GoodieGenerator& g = Context::goodieGenerator();
    Goodie* goodie = g.generate(robot->getTemplate()->goodieProb(),
                                robot->pos());
    if (goodie)
    {
        cxt_.map()->addObj(goodie);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
