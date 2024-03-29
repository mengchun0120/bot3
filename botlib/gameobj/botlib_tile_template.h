#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public CompositeObjectTemplate {
public:
    TileTemplate();

    ~TileTemplate() override = default;

    void init(const std::string &name,
              const rapidjson::Value &v,
              const ComponentTemplateLib &componentTemplateLib);

    inline float hp() const;

    inline float dyingDuration() const;

    inline float touchSpan() const;

protected:
    float hp_;
    float dyingDuration_;
    float touchSpan_;
};

float TileTemplate::hp() const
{
    return hp_;
}

float TileTemplate::dyingDuration() const
{
    return dyingDuration_;
}

float TileTemplate::touchSpan() const
{
    return touchSpan_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

