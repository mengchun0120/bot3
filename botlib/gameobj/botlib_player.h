#ifndef INCLUDED_BOTLIB_PLAYER_H
#define INCLUDED_BOTLIB_PLAYER_H

#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_player_template.h>
#include <botlib_robot.h>
#include <botlib_goodie.h>

namespace mcdane {
namespace botlib {

class Player: public Robot {
public:
    Player() = default;

    ~Player() override = default;

    void init(const PlayerTemplate* t,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1,
              float goodieY,
              float goodieStartX,
              float goodieSpacing);

    inline const PlayerTemplate* getTemplate() const;

    void update(UpdateContext& cxt) override;

    void addGoodie(const GoodieTemplate* t);

    void presentGoodies();

    void toJson(rapidjson::Value& v,
                rapidjson::Document::AllocatorType& allocator) override;

protected:
    void initGoodies();

    void updateGoodies(float timeDelta);

    Goodie* findGoodie(GoodieType type);

    commonlib::Vector2 nextGoodiePos();

    void updateGoodiePos();

protected:
    commonlib::ObjectPool<Goodie> goodiePool_;
    commonlib::LinkedList<Goodie> goodies_;
    float goodieY_;
    float goodieStartX_;
    float goodieSpacing_;
};

const PlayerTemplate* Player::getTemplate() const
{
    return static_cast<const PlayerTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

