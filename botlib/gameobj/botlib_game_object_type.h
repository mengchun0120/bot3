#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TYPE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TYPE_H

#include <string>
#include <ostream>

namespace mcdane {
namespace botlib {

enum class GameObjectType {
    TILE,
    GOODIE,
    ROBOT,
    MISSILE,
    EFFECT,
    COUNT
};

constexpr int k_gameObjTypeCount = static_cast<int>(GameObjectType::COUNT);

inline bool isValidGameObjectType(GameObjectType t)
{
    return static_cast<int>(GameObjectType::TILE) <= static_cast<int>(t) &&
           static_cast<int>(GameObjectType::COUNT) > static_cast<int>(t);
}

inline bool isNonPassthroughObjType(GameObjectType t)
{
    return t == GameObjectType::TILE ||
           t == GameObjectType::ROBOT;
}

inline bool isPassthroughObjType(GameObjectType t)
{
    return t == GameObjectType::MISSILE ||
           t == GameObjectType::GOODIE;
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream &operator<<(ostream& os, mcdane::botlib::GameObjectType t);

} // end of namespace std

#endif

