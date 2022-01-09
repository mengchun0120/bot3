#include <botlib_game_object.h>
#include <botlib_game_object_flag_resetter.h>

namespace mcdane {
namespace botlib {

void GameObjectFlagResetter::reset(GameObject::Flag flag,
                                   bool value)
{
    flag_ = flag;
    value_ = value;
}

bool GameObjectFlagResetter::run(GameObjectList& objList,
                                 GameObject* obj)
{
    obj->setFlag(flag_, value_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

