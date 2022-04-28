#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>

namespace mcdane {
namespace botlib {

GameObjectDumper::GameObjectDumper(int poolSize)
    : pool_(poolSize)
{
    using namespace std::placeholders;

    deleter_ = std::bind(&GameObjectDumper::del, this, _1);
    objs_.setDeleter(&deleter_);
}

void GameObjectDumper::add(GameObject* obj)
{
    Item* item = pool_.alloc();
    item->setObj(obj);
    objs_.pushBack(item);
}

void GameObjectDumper::cleanup(GameMap& map)
{
    Item* item;
    while ((item = objs_.unlinkFront()))
    {
        map.removeObj(item->obj());
        pool_.free(item);
    }
}

void GameObjectDumper::del(Item* item)
{
    pool_.free(item);
}

} // end of namespace botlib
} // end of namespace mcdane

