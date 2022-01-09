#ifndef INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectPresenter: public GameMapAccessor {
public:
    void reset(GameObjectType type);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    inline bool check(GameObject* obj);

private:
    GameObjectType curType_;
};

bool GameObjectPresenter::check(GameObject* obj)
{
    return obj->alive() && obj->type() == curType_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

