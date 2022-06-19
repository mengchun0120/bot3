#include <botlib_game_object.h>
#include <botlib_game_object_presenter.h>

namespace mcdane {
namespace botlib {

bool GameObjectPresenter::run(GameObject* obj)
{
    if (obj->state() == GameObjectState::DEAD)
    {
        return true;
    }

    obj->present();

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

