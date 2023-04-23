#ifndef INCLUDED_BOTLIB_GAME_OBJ_FLAG_RESETTER_H
#define INCLUDED_BOTLIB_GAME_OBJ_FLAG_RESETTER_H

#include <botlib_game_obj_flag.h>

namespace mcdane {
namespace botlib {

class GameObject;

class GameObjFlagResetter {
public:
    GameObjFlagResetter() = default;

    void init(GameObjFlag flag);

    bool operator()(GameObject *obj);

private:
    GameObjFlag flag_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
