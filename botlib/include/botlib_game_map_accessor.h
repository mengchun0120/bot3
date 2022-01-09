#ifndef INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H
#define INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H

#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameMapAccessor {
public:
    GameMapAccessor() = default;

    virtual ~GameMapAccessor() = default;

    virtual bool run(GameObjectList& objList,
                     GameObject* obj) = 0;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

