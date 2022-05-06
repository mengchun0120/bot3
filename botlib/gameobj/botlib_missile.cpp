#include <sstream>
#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_json_utils.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>
#include <botlib_particle_effect.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_game_object_dumper.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Missile::init(const MissileTemplate* t,
                   Side side,
                   const commonlib::Vector2& pos1,
                   const commonlib::Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    damage_ = t->damage();
    resetSpeed();
}

void Missile::update(GameMap& map,
                     GameObjectDumper& dumper,
                     float timeDelta)
{
    if (state_ != GameObjectState::ALIVE)
    {
        GameObject::update(map, dumper, timeDelta);
        return;
    }

    Vector2 delta = speed_ * timeDelta;

    bool collideBoundary = checkRectCollideBoundary(delta, collideRegion(),
                                                    map.boundary(), delta);

    shiftPos(delta);
    map.repositionObj(this);

    bool collideObjs = checkCollideObjs(map);

    if (collideBoundary || collideObjs)
    {
        explode(map, dumper);
    }

    GameObject::update(map, dumper, timeDelta);
}

void Missile::setDirection(const commonlib::Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetSpeed();
}

void Missile::explode(GameMap& map,
                      GameObjectDumper& dumper)
{
    MissileHitChecker checker(this, true, &dumper);
    Region<int> area = map.getCollideArea(explodeRegion());
    map.accessRegion(area, checker);

    showExplodeEffect(map);
    dumper.add(this);
}

void Missile::resetSpeed()
{
    speed_ = speedNorm() * direction_;
}

bool Missile::checkCollideObjs(GameMap& map)
{
    MissileHitChecker checker(this, false);
    Region<int> area = map.getCollideArea(collideRegion());
    map.accessRegion(area, checker);

    return checker.collide();
}

Region<float> Missile::explodeRegion()
{
    float breath = getTemplate()->explodeBreath();
    return Region<float>({x()-breath, x()+breath, y()-breath, y()+breath});
}

void Missile::showExplodeEffect(GameMap& map)
{
    ParticleEffect* explodeEffect = new ParticleEffect();
    explodeEffect->init(getTemplate()->explodeEffectTemplate(), pos_);
    map.addObj(explodeEffect);
}

rapidjson::Value Missile::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Missile", allocator);
    v.AddMember("side", jsonVal(stringVal(side_), allocator), allocator);
    v.AddMember("speed", jsonVal(speed_, allocator), allocator);
    v.AddMember("damage", damage_, allocator);
    v.AddMember("base", CompositeObject::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

