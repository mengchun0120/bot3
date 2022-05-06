#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;
class GameObjectDumper;

class GameObjectUpdater: public GameMapAccessor {
public:
    GameObjectUpdater() = default;

    void init(GameObjectDumper* dumper);

    void reset(float timeDelta);

    bool run(GameMap& map,
             GameObject* obj) override;

private:
    GameObjectDumper* dumper_;
    float timeDelta_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

