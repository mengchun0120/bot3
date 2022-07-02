#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_collide.h>
#include <botlib_missile.h>
#include <botlib_goodie.h>
#include <botlib_player.h>
#include <botlib_game_object_dumper.h>
#include <botlib_passthrough_collide_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

PassthroughCollideChecker::PassthroughCollideChecker(GameMap& map,
                                                     GameObjectDumper& dumper,
                                                     Robot* robot)
    : map_(map)
    , dumper_(dumper)
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
        missile->explode(map_, dumper_);
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
        dumper_.add(goodie);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

