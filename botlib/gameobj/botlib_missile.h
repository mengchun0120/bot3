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
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const MissileTemplate* getTemplate() const;

    inline Side side() const;

    inline float speedNorm() const;

    inline const commonlib::Vector2& speed() const;

    inline float damage() const;

    void update(GameMap& map,
                float timeDelta) override;

    void setDirection(const commonlib::Vector2& direction1) override;

    void explode(GameMap& map);

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

private:
    void resetSpeed();

    bool checkCollideObjs(GameMap& map);

    commonlib::Region<float> explodeRegion();

    void showExplodeEffect(GameMap& map);

private:
    Side side_;
    commonlib::Vector2 speed_;
    float damage_;
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

