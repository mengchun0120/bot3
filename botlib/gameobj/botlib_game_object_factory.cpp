#include <commonlib_log.h>
#include <botlib_tile.h>
#include <botlib_goodie.h>
#include <botlib_missile.h>
#include <botlib_particle_effect.h>
#include <botlib_ai_robot.h>
#include <botlib_player.h>
#include <botlib_game_object_factory.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectFactory::GameObjectFactory()
{
}

void GameObjectFactory::init(int missilePoolSize)
{
    missilePool_.init(missilePoolSize);
    initDeleter();
}

Tile* GameObjectFactory::createTile(const TileTemplate* t,
                                    const commonlib::Vector2& pos,
                                    const commonlib::Vector2& direction)
{
    return new Tile(t, pos, direction);;
}

Goodie* GameObjectFactory::createGoodie(const GoodieTemplate* t,
                                        const commonlib::Vector2& pos,
                                        const commonlib::Vector2& direction)
{
    return new Goodie(t, pos, direction);
}

Missile* GameObjectFactory::createMissile(const MissileTemplate* t,
                                          Side side,
                                          const commonlib::Vector2& pos,
                                          const commonlib::Vector2& direction,
                                          float damageFactor)
{
    return missilePool_.alloc(t, side, pos, direction, damageFactor);
}

ParticleEffect* GameObjectFactory::createParticleEffect(
                                            const ParticleEffectTemplate* t,
                                            const commonlib::Vector2& pos)
{
    return new ParticleEffect(t, pos);
}

AIRobot* GameObjectFactory::createAIRobot(const AIRobotTemplate* t,
                                          const commonlib::Vector2& pos,
                                          const commonlib::Vector2& direction,
                                          GameObjItemDeleter itemDeleter)
{
    return new AIRobot(t, pos, direction, itemDeleter);
}

Player* GameObjectFactory::createPlayer(const PlayerTemplate* t,
                                        const commonlib::Vector2& pos,
                                        const commonlib::Vector2& direction,
                                        float goodieY,
                                        float goodieStartX,
                                        float goodieSpacing,
                                        GameObjItemDeleter itemDeleter)
{
    return new Player(t, pos, direction, goodieY, goodieStartX, goodieSpacing,
                      itemDeleter);
}

void GameObjectFactory::initDeleter()
{
    using namespace std::placeholders;
    deleter_ = std::bind(&GameObjectFactory::free, this, _1);
}

void GameObjectFactory::free(GameObject* obj)
{
    if (obj->getTemplate()->type() != GameObjectType::MISSILE)
    {
        delete obj;
    }
    else
    {
        missilePool_.free(static_cast<Missile*>(obj));
    }
}

} // end of namespace botlib
} // end of namespace mcdane
