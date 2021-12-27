#ifndef INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class NonpassthroughCollideChecker: public GameMapAccessor {
public:
    void reset(GameObject* o,
               const commonlib::Vector2& delta);

    inline bool collide() const;

    inline const commonlib::Vector2& delta() const;

    bool run(ItemList& itemList,
             GameMapItem* item) override;

private:
    inline bool check(GameObject* o) const;

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

