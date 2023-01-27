#ifndef INCLUDED_BOTLIB_MISSILE_H
#define INCLUDED_BOTLIB_MISSILE_H

#include <botlib_missile_template.h>
#include <botlib_composite_object.h>
#include <botlib_side.h>

namespace mcdane {
namespace botlib {

class Robot;

class Missile: public CompositeObject {
public:
    Missile();

    Missile(const MissileTemplate* t,
            Side side,
            const commonlib::Vector2& pos1,
            const commonlib::Vector2& direction1,
            float damageFactor=1.0f);

    ~Missile() override;

    void init(const MissileTemplate* t,
              Side side,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1,
              float damageFactor=1.0f);

    inline const MissileTemplate* getTemplate() const;

    inline Side side() const;

    inline float speedNorm() const;

    inline const commonlib::Vector2& speed() const;

    inline float damage() const;

    void update(UpdateContext& cxt) override;

    void setDirection(const commonlib::Vector2& direction1) override;

    void explode(UpdateContext& cxt);

    bool canBeDumped(GameMap& map) const override;

private:
    void updateAlive(UpdateContext& cxt);

    void updateForTarget(UpdateContext& cxt);

    void resetSpeed();

    bool checkCollideObjs(UpdateContext& cxt);

    commonlib::Region<float> explodeRegion();

    void showExplodeEffect(UpdateContext& cxt);

    void setTarget(const commonlib::Vector2& target);

    void searchAndSetTarget(UpdateContext& cxt);

    commonlib::Region<int> searchRegion(GameMap* map);

    void shootSplitMissile(UpdateContext& cxt);

private:
    Side side_;
    commonlib::Vector2 speed_;
    float damage_;
    float livingTime_;
    bool targetSet_;
    float timeToTarget_;
};

const MissileTemplate* Missile::getTemplate() const
{
    return static_cast<const MissileTemplate*>(t_);
}

Side Missile::side() const
{
    return side_;
}

float Missile::speedNorm() const
{
    return getTemplate()->speed();
}

const commonlib::Vector2& Missile::speed() const
{
    return speed_;
}

float Missile::damage() const
{
    return damage_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

