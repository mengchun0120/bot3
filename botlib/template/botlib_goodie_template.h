#ifndef INCLUDED_BOTLIB_GOODIE_TEMPLATE_H
#define INCLUDED_BOTLIB_GOODIE_TEMPLATE_H

#include <functional>
#include <botlib_goodie_type.h>
#include <botlib_composite_object_template.h>
#include <botlib_goodie_action.h>

namespace mcdane {
namespace botlib {

class Goodie;
class Player;

class GoodieTemplate: public CompositeObjectTemplate {
public:

    GoodieTemplate() = default;

    ~GoodieTemplate() override = default;

    void init(GoodieType goodieType1,
              const rapidjson::Value& v,
              const ComponentTemplateLib& componentTemplateLib,
              const ProgressPieTemplateLib& progressPieTemplateLib);

    inline GoodieType goodieType() const;

    inline float duration() const;

    inline float weight() const;

    inline float factor() const;

    inline const ActivateGoodieAction& activateAction() const;

    inline const DeactivateGoodieAction& deactivateAction() const;

    inline const ProgressPieTemplate* progressPieTemplate() const;

private:
    void initActions();

private:
    GoodieType goodieType_;
    float duration_;
    float weight_;
    float factor_;
    ActivateGoodieAction activateAction_;
    DeactivateGoodieAction deactivateAction_;
    const ProgressPieTemplate* progressPieTemplate_;
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

const ActivateGoodieAction& GoodieTemplate::activateAction() const
{
    return activateAction_;
}

const DeactivateGoodieAction& GoodieTemplate::deactivateAction() const
{
    return deactivateAction_;
}

const ProgressPieTemplate* GoodieTemplate::progressPieTemplate() const
{
    return progressPieTemplate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

