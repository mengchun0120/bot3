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

    GameObjectItem* item = pool_.alloc();
    item->setItem(obj);
    objs_.pushBack(item);
    obj->setState(GameObjectState::DEAD);

    LOG_DEBUG << "dumped " << obj->type() << " " << obj->id() << LOG_END;
}

void GameObjectDumper::clear(GameMap& map)
{
    GameObjectItem* i;
    while ((i = objs_.unlinkFront()))
    {
        LOG_DEBUG << "removed " << i->item()->type() << " "
                  << i->item()->id() << LOG_END;

        map.removeObj(i->item());
        pool_.free(i);
    }
}

void GameObjectDumper::del(GameObjectItem* item)
{
    pool_.free(item);
}

} // end of namespace botlib
} // end of namespace mcdane

