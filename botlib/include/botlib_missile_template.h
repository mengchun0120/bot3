#ifndef INCLUDED_BOTLIB_MISSILE_TEMPLATE_H
#define INCLUDED_BOTLIB_MISSILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class MissileTemplate: public CompositeObjectTemplate {
public:
    MissileTemplate(float collideBreath,
                    float damage,
                    float speed,
                    std::vector<Component>&& components);

    ~MissileTemplate() override = default;

    inline float damage() const;

    inline float speed() const;

private:
    float damage_;
    float speed_;
};

float MissileTemplate::damage() const
{
    return damage_;
}

float MissileTemplate::speed() const
{
    return speed_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

