#ifndef INCLUDED_BOTLIB_GAME_OBJECT_STATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_STATE_H

#include <ostream>

namespace mcdane {
namespace botlib {

enum class GameObjectState {
    ALIVE,
    DYING,
    DEAD
};

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream &operator<<(ostream& os,
                    mcdane::botlib::GameObjectState state);

} // end of namespace std

#endif

