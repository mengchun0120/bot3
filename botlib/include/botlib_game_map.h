#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

class GameMap {
public:
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
                GameObject::Deleter* deleter);

private:
    void initItemDeleter();

private:
    using ItemList = commonlib::LinkedList<GameMapItem>;
    using ItemDeleter = ItemList::Deleter;

private:
    commonlib::ObjectPool<Item> itemPool_;
    ItemDeleter itemDelter_;
    std::vector<std::vector<ItemList>> map_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

