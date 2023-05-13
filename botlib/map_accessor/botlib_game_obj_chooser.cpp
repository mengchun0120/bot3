#include <commonlib_log.h>
#include <botlib_tile.h>
#include <botlib_robot.h>
#include <botlib_game_obj_chooser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjChooser::GameObjChooser()
    : obj_(nullptr)
{}

void GameObjChooser::init(const Vector2 &p)
{
    p_ = p;
    obj_ = nullptr;
}

bool GameObjChooser::operator()(GameObject *o)
{
    if (o->type() != GameObjectType::TILE && o->type() != GameObjectType::ROBOT)
    {
        return true;
    }

    if (o->state() != GameObjectState::ALIVE)
    {
        return true;
    }

    if (o->touched(p_))
    {
        obj_ = o;
        return false;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
