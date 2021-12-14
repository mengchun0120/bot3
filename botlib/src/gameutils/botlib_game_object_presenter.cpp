#include <botlib_game_object_presenter.h>

namespace mcdane {
namespace botlib {

void GameObjectPresenter::reset(GameObjectType type)
{
    curType_ = type;
}

bool GameObjectPresenter::present(GameObject* o)
{
    if (!check(o))
    {
        return true;
    }

    o->present();

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
