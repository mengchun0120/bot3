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
    switch (o->type())
    {
        case GameObjectType::TILE:
            return checkTile(o);
        case GameObjectType::ROBOT:
            return checkRobot(o);
        default:
            break;
    }

    return true;
}

bool GameObjChooser::checkTile(GameObject *o)
{
    if (o->state() != GameObjectState::ALIVE)
    {
        return true;
    }

    Tile *tile = static_cast<Tile *>(o);
    if (tile->touched(p_))
    {
        obj_ = o;
        return false;
    }

    return true;
}

bool GameObjChooser::checkRobot(GameObject *o)
{
    if (o->state() != GameObjectState::ALIVE)
    {
        return true;
    }

    Robot *robot = static_cast<Robot *>(o);
    if (robot->side() != Side::AI)
    {
        return true;
    }

    if (robot->touched(p_))
    {
        obj_ = o;
        return false;
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
