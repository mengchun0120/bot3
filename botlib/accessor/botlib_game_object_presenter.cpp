#include <botlib_game_object.h>
#include <botlib_game_object_presenter.h>

namespace mcdane {
namespace botlib {

void GameObjectPresenter::reset(GameObjectType type)
{
    curType_ = type;
}

bool GameObjectPresenter::run(GameMap& map,
                              GameObject* obj)
{
    if (obj->state() == GameObjectState::DEAD || obj->type() != curType_)
    {
        return true;
    }

    obj->present();

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

