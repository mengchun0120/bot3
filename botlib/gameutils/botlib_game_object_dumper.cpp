#include <commonlib_log.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameObjectDumper::init(int poolSize)
{
    using namespace std::placeholders;

    pool_.init(poolSize);
    deleter_ = std::bind(&GameObjectDumper::del, this, _1);
    objs_.setDeleter(&deleter_);
}

void GameObjectDumper::add(GameObject* obj)
{
    if (obj->state() == GameObjectState::DUMPED)
    {
        return;
    }

    Item* item = pool_.alloc();
    item->setObj(obj);
    objs_.pushBack(item);
    obj->setState(GameObjectState::DUMPED);
}

void GameObjectDumper::clear(GameMap& map)
{
    Item* item;
    while ((item = objs_.unlinkFront()))
    {
        LOG_INFO << "removed " << item->obj()->id() << LOG_END;
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

