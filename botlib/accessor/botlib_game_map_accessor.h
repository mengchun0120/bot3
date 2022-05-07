#ifndef INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H
#define INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H

namespace mcdane {
namespace botlib {

class GameObject;

class GameMapAccessor {
public:
    GameMapAccessor() = default;

    virtual ~GameMapAccessor() = default;

    virtual bool run(GameObject* obj) = 0;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

