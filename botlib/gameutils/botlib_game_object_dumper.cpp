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
    objs_.setDeleter(std::bind(&GameObjectDumper::del, this, _1));
}

void GameObjectDumper::add(GameObject* obj)
{
    if (obj->state() == GameObjectState::DEAD)
    {
        LOG_WARN << "Trying to dump dead object" << LOG_END;
        return;
    }

    Item* item = pool_.alloc();
    item->setObj(obj);
    objs_.pushBack(item);
    obj->setState(GameObjectState::DEAD);

    LOG_DEBUG << "dumped " << obj->type() << " " << obj->id() << LOG_END;
}

void GameObjectDumper::clear(GameMap& map)
{
    Item* item;
    while ((item = objs_.unlinkFront()))
    {
        LOG_DEBUG << "removed " << item->obj()->type() << " "
                  << item->obj()->id() << LOG_END;

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

