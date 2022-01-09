#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

#include <botlib_game_object.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObjectUpdater: public GameMapAccessor {
public:
    void setMap(GameMap* map);

    void setDelta(float delta);

    bool run(GameObjectList& objList,
             GameObject* obj) override;

private:
    inline bool check(GameObject* obj) const;

private:
    GameMap* map_;
    float delta_;
};

bool GameObjectUpdater::check(GameObject* obj) const
{
    return obj->alive() && !obj->updated();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

