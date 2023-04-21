#ifndef INCLUDED_BOTLIB_PLAYER_H
#define INCLUDED_BOTLIB_PLAYER_H

#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_goodie_effect.h>
#include <botlib_robot.h>
#include <botlib_player_template.h>

namespace mcdane {
namespace botlib {

class Player: public Robot {
public:
    Player() = default;

    Player(const PlayerTemplate *t,
           const commonlib::Vector2 &pos1,
           const commonlib::Vector2 &direction1);

    ~Player() override = default;

    void init(const PlayerTemplate *t,
              const commonlib::Vector2 &pos1,
              const commonlib::Vector2 &direction1);

    inline const PlayerTemplate *getTemplate() const;

    inline const GoodieEffectItem *firstGoodieEffect() const;

    void update(UpdateContext &cxt) override;

    void addGoodieEffect(const GoodieTemplate *t);

    void toJson(rapidjson::Value &v,
                rapidjson::Document::AllocatorType &allocator) override;

    void setDest(const commonlib::Vector2 &dest);

#ifdef DESKTOP_APP
    Skill *findSkillForInput(int input);
#endif

protected:
    void initGoodieEffects();

#ifdef DESKTOP_APP
    void initSkillMap();
#endif

    void updateGoodieEffects(float timeDelta);

    GoodieEffectItem *findGoodieEffect(GoodieType type);

protected:
    commonlib::ObjectPool<GoodieEffectItem> goodieEffectPool_;
    commonlib::LinkedList<GoodieEffectItem> goodieEffects_;
#ifdef DESKTOP_APP
    std::unordered_map<int,Skill*> skillMap_;
#endif
};

const PlayerTemplate *Player::getTemplate() const
{
    return static_cast<const PlayerTemplate*>(t_);
}

const GoodieEffectItem *Player::firstGoodieEffect() const
{
    return goodieEffects_.first();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

