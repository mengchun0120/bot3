#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_move_skill.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Player::init(const PlayerTemplate* t,
                  const Vector2& pos1,
                  const Vector2& direction1,
                  float goodieY,
                  float goodieStartX,
                  float goodieSpacing,
                  GameObjItemDeleter itemDeleter)
{
    Robot::init(t, Side::PLAYER, pos1, direction1, itemDeleter);
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

void Player::setDest(const commonlib::Vector2& dest)
{
    MoveSkill* s = static_cast<MoveSkill*>(searchSkill(SkillType::MOVE));
    s->setDest(dest);
    s->setEnabled(true);
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


void Player::updatePos(UpdateContext& cxt)
{
    bool reachDest = false;
    float timeDelta = cxt.timeDelta();
    if (timeDelta >= timeToDest_)
    {
        timeDelta = timeToDest_;
        reachDest = true;
    }

    Vector2 delta = speed_ * timeDelta;
    bool collide = cxt.map()->checkCollision(delta, this);
    shiftPos(delta);
    cxt.map()->repositionObj(this);

    if (reachDest || collide)
    {
        timeToDest_ = 0.0f;
        setMovingEnabled(false);
    }
    else
    {
        timeToDest_ -= cxt.timeDelta();
    }

    checkPassthroughCollide(cxt);
}

void Player::updateGoodies(float timeDelta)
{
    Goodie* g, * next;
    bool updated = false;

    for (g = goodies_.first(); g; g = next)
    {
        next = static_cast<Goodie*>(g->next());

        g->updateActivated(*this, timeDelta);

        if (!g->activated())
        {
            LOG_INFO << "Goodie expired " << g->goodieType()
                     << LOG_END;
            goodies_.remove(g);
            updated = true;
        }
    }

    if (updated)
    {
        updateGoodiePos();
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

void Player::updateGoodiePos()
{
    Vector2 p{goodieStartX_, goodieY_};

    for (Goodie* g = goodies_.first(); g; g = static_cast<Goodie*>(g->next()))
    {
        g->setPos(p);
        p[0] += goodieSpacing_;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

