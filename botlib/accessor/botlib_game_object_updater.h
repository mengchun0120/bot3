#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;
class GameObjectDumper;

class GameObjectUpdater: public GameMapAccessor {
public:
    GameObjectUpdater(GameMap& map,
                      GameObjectDumper& dumper,
                      float timeDelta);

    bool run(GameObject* obj) override;

private:
    GameMap& map_;
    GameObjectDumper& dumper_;
    float timeDelta_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

