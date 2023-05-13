#ifndef INCLUDED_BOTLIB_GAME_OBJ_CHOOSER_H
#define INCLUDED_BOTLIB_GAME_OBJ_CHOOSER_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class GameOject;

class GameObjChooser {
public:
    GameObjChooser();

    void init(const commonlib::Vector2 &p);

    bool operator()(GameObject *o);

    inline GameObject *obj();

private:
    commonlib::Vector2 p_;
    GameObject *obj_;
};

GameObject *GameObjChooser::obj()
{
    return obj_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
