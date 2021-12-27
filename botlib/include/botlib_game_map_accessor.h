#ifndef INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H
#define INCLUDED_BOTLIB_GAME_MAP_ACCESSOR_H

#include <commonlib_linked_list.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

using ItemList = commonlib::LinkedList<GameMapItem>;

class GameMapAccessor {
public:
    GameMapAccessor() = default;

    virtual ~GameMapAccessor() = default;

    virtual bool run(ItemList& itemList,
                     GameMapItem* item) = 0;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

