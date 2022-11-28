#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_update_context.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Player::init(const PlayerTemplate* t,
                  const Vector2& pos1,
                  const Vector2& direction1,
                  float goodieY,
                  float goodieStartX,
                  float goodieSpacing)
{
    Robot::init(t, Side::PLAYER, pos1, direction1);
    initGoodies();
    goodieY_ = goodieY;
    goodieStartX_ = goodieStartX;
    goodieSpacing_ = goodieSpacing;
}

void Player::update(UpdateContext& cxt)
{
    updateGoodies(cxt.timeDelta());
    Robot::update(cxt);
}

void Player::initGoodies()
{
    auto initFunc = [](Goodie& g)
    {
        g.initPie();
    };

    goodiePool_.init(lastingGoodieTypeCount(), initFunc);

    goodies_.setDeleter(
        [this](Goodie* g)
        {
            goodiePool_.free(g);
        }
    );
}

void Player::addGoodie(const GoodieTemplate* t)
{
    Goodie* g = findGoodie(t->goodieType());
    if (g)
    {
        g->reset();
        return;
    }

    g = goodiePool_.alloc();
    g->init(t, nextGoodiePos(), Vector2{1.0f, 0.0f}, true);
    goodies_.pushBack(g);

    LOG_INFO << "Added Goodie " << g->goodieType() << LOG_END;
}

void Player::presentGoodies()
{
    for (Goodie* g = goodies_.first(); g; g = static_cast<Goodie*>(g->next()))
    {
        g->present();
    }
}

void Player::toJson(rapidjson::Value& v,
                    rapidjson::Document::AllocatorType& allocator)
{
    Robot::toJson(v, allocator);
    v.AddMember("type", jsonVal("player", allocator), allocator);
}

void Player::updateGoodies(float timeDelta)
{
    Goodie* g, * next;

    for (g = goodies_.first(); g; g = next)
    {
        next = static_cast<Goodie*>(g->next());

        g->updateActivated(*this, timeDelta);

        if (!g->activated())
        {
            LOG_INFO << "Goodie expired " << g->goodieType()
                     << LOG_END;
            goodies_.remove(g);
        }
    }
}

Goodie* Player::findGoodie(GoodieType type)
{
    Goodie* g;

    for (g = goodies_.first(); g; g = static_cast<Goodie*>(g->next()))
    {
        if (g->goodieType() == type)
        {
            break;
        }
    }

    return g;
}

Vector2 Player::nextGoodiePos()
{
    return Vector2{goodieStartX_ + goodies_.size() * goodieSpacing_,
                   goodieY_};
}

} // end of namespace botlib
} // end of namespace mcdane

