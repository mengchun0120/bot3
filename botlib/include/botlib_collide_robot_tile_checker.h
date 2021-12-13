#ifndef INCLUDED_BOTLIB_COLLIDE_ROBOT_TILE_CHECKER_H
#define INCLUDED_BOTLIB_COLLIDE_ROBOT_TILE_CHECKER_H

#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class CollideRobotTileChecker {
public:

    void reset();

    void setObj(GameObject* o,
                float deltaX,
                float deltaY);

    inline bool collide() const;

    inline float adjustedDeltaX() const;

    inline float adjustedDeltaY() const;

    bool operator()(GameObject* o);

private:
    bool check(GameObject* o) const;

private:
    static CollideRobotTileChecker k_checker;
    float obj_;
    float left_;
    float right_;
    float bottom_;
    float top_;
    bool collide_;
    float adjustedDeltaX_;
    float adjustedDeltaY_;
};

bool CollideRobotTileChecker::collide() const
{
    return collide_;
}

float CollideRobotTileChecker::adjustedDeltaX() const
{
    return adjustedDeltaX_;
}

float CollideRobotTileChecker::adjustedDeltaY() const
{
    return adjustedDeltaY_;
}

bool CollideRobotTileChecker::check(GameObject* o)
{
    return o != obj_ &&
           o->alive() &&
           (o->type() == GameObjectType::ROBOT &&
            o->type() == GameObjectType::TILE);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

