#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class TileTemplate: public CompositeObjectTemplate {
public:
    TileTemplate() = default;

    TileTemplate(float collideBreath,
                 float hp,
                 bool invincible,
                 std::vector<Component>&& components);

    ~TileTemplate() override = default;

    void init(float collideBreath,
              float hp,
              bool invincible,
              std::vector<Component>&& components);

    void init(const rapidjson::Value& v,
              const ComponentTemplateLib& componentTemplateLib);

    inline float hp() const;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

protected:
    float hp_;
};

float TileTemplate::hp() const
{
    return hp_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

