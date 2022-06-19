#ifndef INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_PRESENTER_H

#include <botlib_game_object_type.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectPresenter: public GameMapAccessor {
public:
    GameObjectPresenter() = default;

    bool run(GameObject* obj) override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

