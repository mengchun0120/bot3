#ifndef INCLUDED_BOTLIB_GAME_OBJECT_DUMPER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_DUMPER_H

#include <commonlib_object_pool.h>
#include <commonlib_linked_list.h>
#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObjectDumper {
private:
    class Item {
    public:
        inline Item();

        inline Item(GameObject* obj1);

        ~Item() = default;

        inline GameObject* obj() const;

        inline Item* next();

        inline const Item* next() const;

        inline Item* prev();

        inline const Item* prev() const;

        inline void setObj(GameObject* obj1);

        inline void setPrev(Item* prev1);

        inline void setNext(Item* next1);

        inline void reset();

    private:
        GameObject* obj_;
        Item* prev_;
        Item* next_;
    };

public:
    GameObjectDumper() = default;

    ~GameObjectDumper() = default;

    void init(int poolSize);

    void add(GameObject* obj);

    inline bool empty() const;

    void clear(GameMap& map);

private:
    void del(Item* item);

private:
    commonlib::LinkedList<Item> objs_;
    commonlib::ObjectPool<Item> pool_;
};

GameObjectDumper::Item::Item()
    : obj_(nullptr)
    , prev_(nullptr)
    , next_(nullptr)
{
}

GameObjectDumper::Item::Item(GameObject* obj1)
    : obj_(obj1)
    , prev_(nullptr)
    , next_(nullptr)
{
}

GameObject* GameObjectDumper::Item::obj() const
{
    return obj_;
}

GameObjectDumper::Item* GameObjectDumper::Item::next()
{
    return next_;
}

const GameObjectDumper::Item* GameObjectDumper::Item::next() const
{
    return next_;
}

GameObjectDumper::Item* GameObjectDumper::Item::prev()
{
    return prev_;
}

const GameObjectDumper::Item* GameObjectDumper::Item::prev() const
{
    return prev_;
}

void GameObjectDumper::Item::setObj(GameObject* obj1)
{
    obj_ = obj1;
}

void GameObjectDumper::Item::setPrev(Item* prev1)
{
    prev_ = prev1;
}

void GameObjectDumper::Item::setNext(Item* next1)
{
    next_ = next1;
}

void GameObjectDumper::Item::reset()
{
    obj_ = nullptr;
    prev_ = nullptr;
    next_ = nullptr;
}

bool GameObjectDumper::empty() const
{
    return objs_.empty();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

