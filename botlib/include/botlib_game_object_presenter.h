#ifndef INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H

#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class GameObjectPresenter {
public:
    GameObjectPresenter() = default;

    ~GameObjectPresenter() = default;

    void reset(GameObjectType type);

    bool present(GameObject* o);

    inline bool check(GameObject* o);

private:
    GameObjectType curType_;
};

bool GameObjectPresenter::check(GameObject* o)
{
    return o->alive() && o->type() == curType_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

