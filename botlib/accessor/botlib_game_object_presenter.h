#ifndef INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectPresenter: public GameMapAccessor {
public:
    GameObjectPresenter() = default;

    void reset(GameObjectType type);

    bool run(GameMap& map,
             GameObject* obj) override;

private:
    GameObjectType curType_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

