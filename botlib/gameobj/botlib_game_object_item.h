#ifndef INCLUDED_BOTLIB_GAME_OBJECT_ITEM_H
#define INCLUDED_BOTLIB_GAME_OBJECT_ITEM_H

namespace mcdane {
namespace botlib {

class GameObject;

class GameObjectItem {
public:
    inline GameObjectItem();

    inline GameObjectItem(GameObject* obj1);

    ~GameObjectItem() = default;

    inline GameObject* obj() const;

    inline GameObjectItem* next();

    inline const GameObjectItem* next() const;

    inline GameObjectItem* prev();

    inline const GameObjectItem* prev() const;

    inline void setObj(GameObject* obj1);

    inline void setPrev(GameObjectItem* prev1);

    inline void setNext(GameObjectItem* next1);

    inline void reset();

private:
    GameObject* obj_;
    GameObjectItem* prev_;
    GameObjectItem* next_;
};

GameObjectItem::GameObjectItem()
    : obj_(nullptr)
    , prev_(nullptr)
    , next_(nullptr)
{
}

GameObjectItem::GameObjectItem(GameObject* obj1)
    : obj_(obj1)
    , prev_(nullptr)
    , next_(nullptr)
{
}

GameObject* GameObjectItem::obj() const
{
    return obj_;
}

GameObjectItem* GameObjectItem::next()
{
    return next_;
}

const GameObjectItem* GameObjectItem::next() const
{
    return next_;
}

GameObjectItem* GameObjectItem::prev()
{
    return prev_;
}

const GameObjectItem* GameObjectItem::prev() const
{
    return prev_;
}

void GameObjectItem::setObj(GameObject* obj1)
{
    obj_ = obj1;
}

void GameObjectItem::setPrev(GameObjectItem* prev1)
{
    prev_ = prev1;
}

void GameObjectItem::setNext(GameObjectItem* next1)
{
    next_ = next1;
}

void GameObjectItem::reset()
{
    obj_ = nullptr;
    prev_ = nullptr;
    next_ = nullptr;
}


} // end of namespace botlib
} // end of namespace mcdane

#endif
