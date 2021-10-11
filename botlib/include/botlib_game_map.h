#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class GameMap {
public:
    using GameObjectDeleter = std::function<void(GameObject*)>;

    GameMap();

    GameMap(unsigned int rows,
            unsigned int cols,
            unsigned int poolSize);

    ~GameMap();

    void init(unsigned int rows,
              unsigned int cols,
              unsigned int poolSize);

    void present() const;

    void addObj(GameObject* obj,
                GameObjectDeleter* deleter);

private:
    class Item {
    public:
        inline Item();

        inline void init(GameObject* obj,
                         GameObjectDeleter* deleter);

        inline Item* next();

        inline const Item* next() const;

        inline void setNext(Item* item);

        inline GameObject* obj();

        inline const GameObject* obj() const;

        inline void setObj(GameObject* o);

    private:
        GameObject* obj_;
        Item* next_;
        GameObjectDeleter* deleter_;
    };

    using ItemList = commonlib::LinkedList<Item>;
    using ItemDeleter = ItemList::Deleter;

private:
    commonlib::ObjectPool<Item> itemPool_;
    ItemDeleter itemDelter_;
    std::vector<std::vector<ItemList>> map_;
};

GameMap::Item::Item()
    : obj_(nullptr)
    , next_(nullptr)
{

}

Item* GameMap::Item::next()
{
    return next_;
}

const Item* GameMap::Item::next() const
{
    return next_;
}

void GameMap::Item::setNext(GameMap::Item* item)
{
    next_ = item;
}

GameObject* GameMap::Item::obj()
{
    return obj_;
}

const GameObject* GameMap::Item::obj() const
{
    return obj_;
}

void GameMap::Item::setObj(GameObject* o)
{
    obj_ = o;
}

GameMap::ItemDeleter::ItemDeleter(commonlib::ObjectPool<GameMap::Item>& pool)
    : pool_(pool)
{
}

void GameMap::ItemDeleter::operator()(GameMap::Item *i)
{
    pool_.free(i);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

