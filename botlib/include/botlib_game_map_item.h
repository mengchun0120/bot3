#ifndef INCLUDED_BOTLIB_GAME_MAP_ITEM_H
#define INCLUDED_BOTLIB_GAME_MAP_ITEM_H

#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class GameMapItem {
public:
    GameMapItem();

    void init(GameObject* o,
              GameObject::Deleter* deleter=&GameObject::k_defaultDeleter);

    inline GameObject* obj();

    inline const GameObject* obj() const;

    void setObj(GameObject* o);

    void setDeleter(GameObject::Deleter* deleter);

    void deleteObj();

    inline GameMapItem* next();

    inline const GameMapItem* next() const;

    inline void setNext(GameMapItem* item);

    inline GameMapItem* prev();

    inline const GameMapItem* prev() const;

    inline void setPrev(GameMapItem* item);

private:
    GameObject* obj_;
    GameObject::Deleter* deleter_;
    GameMapItem* next_;
    GameMapItem* prev_;
};

GameObject* GameMapItem::obj()
{
    return obj_;
}

const GameObject* GameMapItem::obj() const
{
    return obj_;
}

GameMapItem* GameMapItem::next()
{
    return next_;
}

const GameMapItem* GameMapItem::next() const
{
    return next_;
}

void GameMapItem::setNext(GameMapItem* item)
{
    next_ = item;
}

GameMapItem* GameMapItem::prev()
{
    return prev_;
}

const GameMapItem* GameMapItem::prev() const
{
    return prev_;
}

void GameMapItem::setPrev(GameMapItem* item)
{
    prev_ = item;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

