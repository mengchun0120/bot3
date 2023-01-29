#ifndef INCLUDED_BOTLIB_GAME_OBJECT_FACTROY_H
#define INCLUDED_BOTLIB_GAME_OBJECT_FACTROY_H

#include <commonlib_vector.h>
#include <commonlib_object_pool.h>
#include <botlib_missile.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameObject;
class Tile;
class Goodie;
class ParticleEffect;
class AIRobot;
class Player;
class PlayerTemplate;

class GameObjectFactory {
public:
    GameObjectFactory();

    ~GameObjectFactory() = default;

    void init(int missilePoolSize);

    Tile* createTile(const TileTemplate* t,
                     const commonlib::Vector2& pos,
                     const commonlib::Vector2& direction);

    Goodie* createGoodie(const GoodieTemplate* t,
                         const commonlib::Vector2& pos,
                         const commonlib::Vector2& direction);

    Missile* createMissile(const MissileTemplate* t,
                           Side side,
                           const commonlib::Vector2& pos,
                           const commonlib::Vector2& direction,
                           float damageFactor=1.0f);

    ParticleEffect* createParticleEffect(const ParticleEffectTemplate* t,
                                         const commonlib::Vector2& pos);

    AIRobot* createAIRobot(const AIRobotTemplate* t,
                           const commonlib::Vector2& pos,
                           const commonlib::Vector2& direction);

    Player* createPlayer(const PlayerTemplate* t,
                         const commonlib::Vector2& pos,
                         const commonlib::Vector2& direction);

    inline GameObjDeleter& deleter();

private:
    void initDeleter();

    void free(GameObject* obj);

protected:
    GameObjDeleter deleter_;
    commonlib::ObjectPool<Missile> missilePool_;
};

GameObjDeleter& GameObjectFactory::deleter()
{
    return deleter_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
