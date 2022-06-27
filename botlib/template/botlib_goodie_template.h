#ifndef INCLUDED_BOTLIB_GOODIE_TEMPLATE_H
#define INCLUDED_BOTLIB_GOODIE_TEMPLATE_H

#include <functional>
#include <botlib_goodie_type.h>
#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class Goodie;
class Player;

class GoodieTemplate: public CompositeObjectTemplate {
public:

    GoodieTemplate() = default;

    ~GoodieTemplate() override = default;

    void init(GoodieType type1,
              const rapidjson::Value& v,
              const ComponentTemplateLib& componentTemplateLib);

    inline GoodieType type() const;

    inline float duration() const;

    inline float weight() const;

    inline float factor() const;

private:
    GoodieType type_;
    float duration_;
    float weight_;
    float factor_;
};

GoodieType GoodieTemplate::type() const
{
    return type_;
}

float GoodieTemplate::duration() const
{
    return duration_;
}

float GoodieTemplate::weight() const
{
    return weight_;
}

float GoodieTemplate::factor() const
{
    return factor_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

