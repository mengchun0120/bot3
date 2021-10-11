#include <commonlib_exception.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

GameMapItem::GameMapItem()
    : obj_(nullptr)
    , next_(nullptr)
    , prev_(nullptr)
{
}

void GameMapItem::init(GameObject* o)
{
    if (!o)
    {
        THROW_EXCEPT(InvalidArgumentException, "obj is null");
    }

    obj_ = o;
    next_ = nullptr;
    prev_ = nullptr;
}

void GameMapItem::setObj(GameObject* o)
{
    if (!o)
    {
        THROW_EXCEPT(InvalidArgumentException, "obj is null");
    }

    obj_ = o;
}

void GameMapItem::setDeleter(GameObject::Deleter* deleter)
{
    deleter_ = deleter;
}

void GameMapItem::deleteObj()
{
    if (deleter_ && obj_)
    {
        (*deleter_)(obj_);
    }

    obj_ = nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane

