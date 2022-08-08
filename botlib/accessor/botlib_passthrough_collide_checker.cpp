#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_collide.h>
#include <botlib_missile.h>
#include <botlib_goodie.h>
#include <botlib_player.h>
#include <botlib_update_context.h>
#include <botlib_game_object_dumper.h>
#include <botlib_passthrough_collide_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

PassthroughCollideChecker::PassthroughCollideChecker(UpdateContext& cxt,
                                                     Robot* robot)
    : cxt_(cxt)
    , robot_(robot)
{
}

bool PassthroughCollideChecker::run(GameObject* obj)
{
    switch (obj->type())
    {
        case GameObjectType::MISSILE:
            collideMissile(static_cast<Missile*>(obj));
            break;
        case GameObjectType::GOODIE:
            collideGoodie(static_cast<Goodie*>(obj));
            break;
        default:
            break;
    }

    return true;
}

void PassthroughCollideChecker::collideMissile(Missile* missile)
{
    if (missile->state() != GameObjectState::ALIVE || missile->side() == robot_->side())
    {
        return;
    }

    bool collide = checkRectCollideRect(robot_->collideRegion(),
                                        missile->collideRegion());
    if (collide)
    {
        missile->explode(cxt_);
    }
}

void PassthroughCollideChecker::collideGoodie(Goodie* goodie)
{
    if (goodie->state() != GameObjectState::ALIVE || robot_->side() != Side::PLAYER)
    {
        return;
    }

    Player* player = static_cast<Player*>(robot_);

    bool collide = checkRectCollideRect(player->collideRegion(),
                                        goodie->collideRegion());
    if (collide)
    {
        goodie->activate(*player);
        LOG_INFO << "Activated goodie " << goodie->type() << LOG_END;
        cxt_.dumper()->add(goodie);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

