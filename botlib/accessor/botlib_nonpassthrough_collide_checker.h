#ifndef INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_NONPASSTHROUGH_COLLIDE_CHECKER_H

#include <commonlib_vector.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class NonpassthroughCollideChecker: public GameMapAccessor {
public:
    NonpassthroughCollideChecker(const GameObject* obj,
                                 commonlib::Vector2& delta1);

    inline bool collide() const;

    inline const commonlib::Vector2& delta() const;

    bool run(GameObject* obj) override;

private:
    const GameObject* obj_;
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

} // end of namespace botlib
} // end of namespace mcdane

#endif

