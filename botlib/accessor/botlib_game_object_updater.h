#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class UpdateContext;

class GameObjectUpdater: public GameMapAccessor {
public:
    GameObjectUpdater(UpdateContext& cxt);

    bool run(GameObject* obj) override;

private:
    UpdateContext& cxt_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

