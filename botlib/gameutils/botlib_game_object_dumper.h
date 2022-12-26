#ifndef INCLUDED_BOTLIB_GAME_OBJECT_DUMPER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_DUMPER_H

#include <commonlib_linked_item.h>
#include <commonlib_object_pool.h>
#include <commonlib_linked_list.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObjectDumper {
private:

public:
    GameObjectDumper() = default;

    ~GameObjectDumper() = default;

    void init(GameObjItemPool* pool);

    void add(GameObject* obj);

    inline bool empty() const;

    void clear(GameMap& map);

private:
    commonlib::LinkedList<GameObjectItem> objs_;
    GameObjItemPool* pool_;
};

bool GameObjectDumper::empty() const
{
    return objs_.empty();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

