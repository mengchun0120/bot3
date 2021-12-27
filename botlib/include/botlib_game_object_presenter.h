#ifndef INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectPresenter: public GameMapAccessor {
public:
    void reset(GameObjectType type);

    bool run(ItemList& itemList,
             GameMapItem* item) override;

private:
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

