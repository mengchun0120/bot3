#ifndef INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class NonpassthroughCollideChecker: public GameMapAccessor {
public:
    void reset(GameObject* obj,
               const commonlib::Vector2& delta);

    inline bool collide() const;

    inline const commonlib::Vector2& delta() const;

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    inline bool check(GameObject* obj) const;

private:
    GameObject* obj_;
    bool collide_;
    commonlib::Vector2 delta_;
};

bool NonpassthroughCollideChecker::collide() const
{
    return collide_;
}

const commonlib::Vector2& NonpassthroughCollideChecker::delta() const
{
    return delta_;
}

bool NonpassthroughCollideChecker::check(GameObject* obj) const
{
    return obj != obj_ &&
           obj->alive() &&
           (obj->type() == GameObjectType::ROBOT ||
            obj->type() == GameObjectType::TILE);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

