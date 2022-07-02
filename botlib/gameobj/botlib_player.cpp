#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Player::init(const PlayerTemplate* t,
                  const Vector2& pos1,
                  const Vector2& direction1)
{
    Robot::init(t, Side::PLAYER, pos1, direction1);
    initEffects();
}

rapidjson::Value Player::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Player", allocator);
    v.AddMember("base", Robot::toJson(allocator), allocator);

    return v;
}

void Player::update(GameMap& map,
                    GameObjectDumper& dumper,
                    float timeDelta)
{
    updateGoodieEffects(timeDelta);
    Robot::update(map, dumper, timeDelta);
}

void Player::initEffects()
{
    effectPool_.init(lastingGoodieTypeCount());

    effects_.setDeleter(
        [this](GoodieEffect* e)
        {
            effectPool_.free(e);
        }
    );
}

void Player::updatePos(GameMap& map,
                       GameObjectDumper& dumper,
                       float timeDelta)
{
    Robot::updatePos(map, dumper, timeDelta);
}

void Player::addGoodieEffect(const GoodieTemplate* t)
{
    GoodieEffect* e = findGoodieEffect(t->goodieType());
    if (e)
    {
        e->reset();
        return;
    }

    e = effectPool_.alloc();
    e->init(t);
    effects_.pushBack(e);

    LOG_INFO << "Added GoodieEffect " << e->type() << LOG_END;
}

void Player::updateGoodieEffects(float timeDelta)
{
    GoodieEffect* e, * next;

    for (e = effects_.first(); e; e = next)
    {
        next = e->next();

        if (e->update(*this, timeDelta))
        {
            LOG_INFO << "GoodieEffect expired " << e->type() << LOG_END;
            effects_.remove(e);
        }
    }
}

GoodieEffect* Player::findGoodieEffect(GoodieType type)
{
    GoodieEffect* e;

    for (e = effects_.first(); e; e = e->next())
    {
        if (e->type() == type)
        {
            break;
        }
    }

    return e;
}

} // end of namespace botlib
} // end of namespace mcdane

