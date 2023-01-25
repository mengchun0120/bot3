#ifndef INCLUDED_BOTLIB_UPDATE_CONTEXT_H
#define INCLUDED_BOTLIB_UPDATE_CONTEXT_H

#include <commonlib_object_pool.h>
#include <botlib_game_object_factory.h>
#include <botlib_game_object_dumper.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameMap;
class GameObjectDumper;

class UpdateContext {
public:
    UpdateContext() = default;

    void init(GameMap* map1,
              int itemPoolSize,
              int missilePoolSize);

    inline GameMap* map();

    inline GameObjItemPool& itemPool();

    inline GameObjectFactory& factory();

    inline GameObjectDumper& dumper();

    inline float timeDelta();

    void setTimeDelta(float timeDelta1);

private:
    GameMap* map_;
    GameObjItemPool itemPool_;
    GameObjectFactory factory_;
    GameObjectDumper dumper_;
    float timeDelta_;
};

GameMap* UpdateContext::map()
{
    return map_;
}

GameObjItemPool& UpdateContext::itemPool()
{
    return itemPool_;
}

GameObjectFactory& UpdateContext::factory()
{
    return factory_;
}

GameObjectDumper& UpdateContext::dumper()
{
    return dumper_;
}

float UpdateContext::timeDelta()
{
    return timeDelta_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

