#include <commonlib_log.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameObjectDumper::init(GameObjItemPool* pool)
{
    pool_ = pool;
    objs_.setDeleter(pool_->deleter());
}

void GameObjectDumper::add(GameObject* obj)
{
    if (obj->state() == GameObjectState::DEAD)
    {
        LOG_WARN << "Trying to dump dead object" << LOG_END;
        return;
    }

    GameObjectItem* item = pool_->alloc(obj);
    objs_.pushBack(item);
    obj->setState(GameObjectState::DEAD);
}

void GameObjectDumper::clear(GameMap& map)
{
    GameObjectItem* i;
    while ((i = objs_.unlinkFront()))
    {
        map.removeObj(i->item());
        pool_->free(i);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

