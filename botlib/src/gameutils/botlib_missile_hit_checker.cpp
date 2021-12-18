#include <commonlib_collide.h>
#include <botlib_tile.h>
#include <botlib_missile_hit_checker.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void MissileHitChecker::reset(Missile* missile)
{
    collide_ = false;
    missile_ = missile;
    left_ = missile_->collideLeft();
    right_ = missile_->collideRight();
    bottom_ = missile_->collideBottom();
    top_ = missile_->collideTop();
}

bool MissileHitChecker::run(GameObject* o)
{
    if (!check(o))
    {
        return true;
    }

    bool collide1 = checkRectCollideRect(left_, right_, bottom_, top_,
                                         o->collideLeft(), o->collideRight(),
                                         o->collideBottom(), o->collideTop());
    if (collide1)
    {
        collide_ = true;
    }

    if (o->type() == GameObjectType::ROBOT)
    {
        Robot* robot = static_cast<Robot*>(o);
        robot->addHP(-missile_->damage());
    }
    else if (o->type() == GameObjectType::TILE)
    {
        Tile* tile = static_cast<Tile*>(o);
        tile->addHP(-missile_->damage());
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane