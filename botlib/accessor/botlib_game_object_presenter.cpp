#include <botlib_game_object.h>
#include <botlib_game_object_presenter.h>

namespace mcdane {
namespace botlib {

void GameObjectPresenter::reset(GameObjectType type)
{
    curType_ = type;
}

bool GameObjectPresenter::run(GameObjectList& objList,
                              GameObject* obj)
{
    if (!obj->alive() || obj->type() != curType_)
    {
        return true;
    }

    obj->present();

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

