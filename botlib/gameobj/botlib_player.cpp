#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_move_skill.h>
#include <botlib_goodie_template.h>
#include <botlib_goodie_action.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Player::Player(const PlayerTemplate* t,
               const commonlib::Vector2& pos1,
               const commonlib::Vector2& direction1)
{
    init(t, pos1, direction1);
}

void Player::init(const PlayerTemplate* t,
                  const Vector2& pos1,
                  const Vector2& direction1)
{
    Robot::init(t, Side::PLAYER, pos1, direction1);
    initGoodieEffects();
    initSkillMap();
}

void Player::update(UpdateContext& cxt)
{
    updateGoodieEffects(cxt.timeDelta());
    Robot::update(cxt);
}

void Player::addGoodieEffect(const GoodieTemplate* t)
{
    if (!isLasting(t->goodieType()))
    {
        activateGoodie(t, *this);
        return;
    }

    GoodieEffectItem* g = findGoodieEffect(t->goodieType());
    if (g)
    {
        g->item().reset();
        return;
    }

    activateGoodie(t, *this);
    g = goodieEffectPool_.alloc(t->goodieType(), t->duration());
    goodieEffects_.pushBack(g);
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

Skill* Player::findSkillForInput(int input)
{
    auto it = skillMap_.find(input);
    return it != skillMap_.end() ? it->second : nullptr;
}

void Player::initGoodieEffects()
{
    goodieEffectPool_.init(lastingGoodieTypeCount());
    goodieEffects_.setDeleter(goodieEffectPool_.deleter());
}

void Player::initSkillMap()
{
    auto& m = getTemplate()->inputSkillMap();
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        Skill* skill = searchSkill(it->second);
        if (!skill)
        {
            LOG_WARN << "Skill " << toString(it->second)
                     << " not configured for player" << LOG_END;
            continue;
        }

        skillMap_[it->first] = skill;
    }
}

void Player::updateGoodieEffects(float timeDelta)
{
    GoodieEffectItem* g, * next;

    for (g = goodieEffects_.first(); g; g = next)
    {
        GoodieEffect& effect = g->item();

        next = g->next();

        effect.reduceTimeToLive(timeDelta);
        if (effect.expired())
        {
            LOG_INFO << "Goodie expired " << effect.type() << LOG_END;
            deactivateGoodie(effect.type(), *this);
            goodieEffects_.remove(g);
        }
    }
}

GoodieEffectItem* Player::findGoodieEffect(GoodieType type)
{
    GoodieEffectItem* g;
    for (g = goodieEffects_.first(); g; g = g->next())
    {
        if (g->item().type() == type)
        {
            return g;
        }
    }

    return nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane

