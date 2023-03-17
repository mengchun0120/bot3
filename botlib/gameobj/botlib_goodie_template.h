#ifndef INCLUDED_BOTLIB_GOODIE_TEMPLATE_H
#define INCLUDED_BOTLIB_GOODIE_TEMPLATE_H

#include <botlib_goodie_type.h>
#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class GoodieTemplate: public CompositeObjectTemplate {
public:
    GoodieTemplate() = default;

    ~GoodieTemplate() override = default;

    void init(GoodieType goodieType1,
              const std::string &name,
              const rapidjson::Value &v,
              const ComponentTemplateLib &componentTemplateLib);

    inline GoodieType goodieType() const;

    inline float duration() const;

    inline float weight() const;

    inline float factor() const;

private:
    GoodieType goodieType_;
    float duration_;
    float weight_;
    float factor_;
};

GoodieType GoodieTemplate::goodieType() const
{
    return goodieType_;
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

