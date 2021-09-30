#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TYPE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TYPE_H

namespace mcdane {
namespace botlib {

enum class GameObjectType {
    TILE,
    ROBOT,
    BULLET,
    EFFECT,
    INVALID
};

inline bool isValidGameObjectType(GameObjectType t)
{
    return static_cast<int>(GameObjectType::TILE) <= static_cast<int>(t) &&
           static_cast<int>(GameObjectType::INVALID) > static_cast<int>(t);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

