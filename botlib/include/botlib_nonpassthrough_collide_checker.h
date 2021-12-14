#ifndef INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H

#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class NonpassthroughCollideChecker {
public:
    NonpassthroughCollideChecker() = default;

    ~NonpassthroughCollideChecker() = default;

    void reset(GameObject* o,
               float deltaX,
               float deltaY);

    inline bool collide() const;

    inline float adjustedDeltaX() const;

    inline float adjustedDeltaY() const;

    inline bool check(GameObject* o) const;

    bool run(GameObject* o);

private:
    GameObject* obj_;
    float left_;
    float right_;
    float bottom_;
    float top_;
    bool collide_;
    float adjustedDeltaX_;
    float adjustedDeltaY_;
};

bool NonpassthroughCollideChecker::collide() const
{
    return collide_;
}

float NonpassthroughCollideChecker::adjustedDeltaX() const
{
    return adjustedDeltaX_;
}

float NonpassthroughCollideChecker::adjustedDeltaY() const
{
    return adjustedDeltaY_;
}

bool NonpassthroughCollideChecker::check(GameObject* o) const
{
    return o != obj_ &&
           o->alive() &&
           (o->type() == GameObjectType::ROBOT ||
            o->type() == GameObjectType::TILE);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

