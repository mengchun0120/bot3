#ifndef INCLUDED_BOTLIB_UPDATE_CONTEXT_H
#define INCLUDED_BOTLIB_UPDATE_CONTEXT_H

namespace mcdane {
namespace botlib {

class GameMap;
class GameObjectDumper;

class UpdateContext {
public:
    UpdateContext() = default;

    void init(GameMap* map1,
              GameObjectDumper* dumper1);

    inline GameMap* map();

    inline GameObjectDumper* dumper();

    inline float timeDelta();

    void setTimeDelta(float timeDelta1);

private:
    GameMap* map_;
    GameObjectDumper* dumper_;
    float timeDelta_;
};

GameMap* UpdateContext::map()
{
    return map_;
}

GameObjectDumper* UpdateContext::dumper()
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

