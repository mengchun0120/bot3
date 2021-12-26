#ifndef INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_UPDATER_H

namespace mcdane {
namespace botlib {

class GameObject;
class GameMap;

class GameObjectUpdater {
public:
    void setMap(GameMap* map);

    void setDelta(float delta);

    bool run(GameObject* o);

private:
    inline bool check(GameObject* o) const;

private:
    GameMap* map_;
    float delta_;
};

bool GameObjectUpdater::check(GameObject* o) const
{
    return o->alive() && !o->updated();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

