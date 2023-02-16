#ifndef INCLUDED_BOTLIB_GAME_OBJ_FLAG_H
#define INCLUDED_BOTLIB_GAME_OBJ_FLAG_H

namespace mcdane {
namespace botlib {

enum class GameObjFlag {
    INVINCIBLE  = 0x00000001,
    UPDATED     = 0x00000002,
    GUIDED      = 0x00000004,
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
