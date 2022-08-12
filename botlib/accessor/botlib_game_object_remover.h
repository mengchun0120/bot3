#ifndef INCLUDED_BOTLIB_GAME_OBJECT_REMOVER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_REMOVER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectDumper;
class GameMap;

class GameObjectRemover: public GameMapAccessor {
public:
    GameObjectRemover(GameObjectDumper& dumper,
                      GameMap& map);

    void init();

    bool run(GameObject* obj) override;

private:
    GameObjectDumper& dumper_;
    GameMap& map_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
