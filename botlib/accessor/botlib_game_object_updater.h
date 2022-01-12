#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObjectUpdater: public GameMapAccessor {
public:
    GameObjectUpdater() = default;

    GameObjectUpdater(GameMap* map,
                      float delta);

    void reset(GameMap* map,
               float delta);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    GameMap* map_;
    float delta_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

