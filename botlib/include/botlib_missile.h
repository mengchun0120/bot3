#ifndef INCLUDED_BOTLIB_MISSILE_H
#define INCLUDED_BOTLIB_MISSILE_H

#include <botlib_missile_template.h>
#include <botlib_composite_object.h>
#include <botlib_side.h>

namespace mcdane {
namespace botlib {

class Missile: public CompositeObject {
public:
    Missile() = default;

    ~Missile() override = default;

    void init(const MissileTemplate* t,
              Side side,
              float x,
              float y,
              float directionX,
              float directionY);

    void init(const MissileTemplate* t,
              Side side,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const MissileTemplate* getTemplate() const;

    inline Side side() const;

    inline float speed() const;

    inline float speedX() const;

    inline float speedY() const;

    inline float damage() const;

    void update(GameMap& map,
                float timeDelta) override;

    void setDirection(float directionX,
                      float directionY) override;

private:
    void resetSpeed();

private:
    Side side_;
    float speedX_;
    float speedY_;
};

const MissileTemplate* Missile::getTemplate() const
{
    return static_cast<const MissileTemplate*>(t_);
}

Side Missile::side() const
{
    return side_;
}

float Missile::speed() const
{
    return getTemplate()->speed();
}

float Missile::speedX() const
{
    return speedX_;
}

float Missile::speedY() const
{
    return speedY_;
}

float Missile::damage() const
{
    return getTemplate()->damage();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

