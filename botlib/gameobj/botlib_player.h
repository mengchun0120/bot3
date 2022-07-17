#ifndef INCLUDED_BOTLIB_PLAYER_H
#define INCLUDED_BOTLIB_PLAYER_H

#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_player_template.h>
#include <botlib_robot.h>
#include <botlib_goodie_effect.h>

namespace mcdane {
namespace botlib {

class Player: public Robot {
public:
    Player() = default;

    ~Player() override = default;

    void init(const PlayerTemplate* t,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const PlayerTemplate* getTemplate() const;

    void update(GameMap& map,
                GameObjectDumper& dumper,
                float timeDelta) override;

    void addGoodieEffect(const GoodieTemplate* t);

protected:
    void initEffects();

    void updateGoodieEffects(float timeDelta);

    GoodieEffect* findGoodieEffect(GoodieType type);

protected:
    using EffectList = commonlib::LinkedList<GoodieEffect>;
    using EffectPool = commonlib::ObjectPool<GoodieEffect>;

    EffectPool effectPool_;
    EffectList effects_;
};

const PlayerTemplate* Player::getTemplate() const
{
    return static_cast<const PlayerTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

