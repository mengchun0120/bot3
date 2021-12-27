#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObjectUpdater: public GameMapAccessor {
public:
    void setMap(GameMap* map);

    void setDelta(float delta);

    bool run(ItemList& itemList,
             GameMapItem* item) override;

private:
    inline bool check(GameObject* o) const;

private:
    GameMap* map_;
    float delta_;
};

bool GameObjectUpdater::check(GameObject* o) const
{
    return o->alive() && !o->updated();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

