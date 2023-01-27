#ifndef INCLUDED_BOTLIB_COMPOSITE_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_COMPOSITE_OBJECT_TEMPLATE_H

#include <vector>
#include <botlib_component.h>
#include <botlib_typedef.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class CompositeObjectTemplate: public GameObjectTemplate {
public:
    CompositeObjectTemplate() = default;

    ~CompositeObjectTemplate() override = default;

    void init(GameObjectType t,
              const std::string& name,
              const rapidjson::Value& v,
              const ComponentTemplateLib& componentTemplateLib);

    inline unsigned int numComponents() const;

    inline const Component& component(unsigned int i) const;

    inline const std::vector<Component>& components() const;

private:
    void initComponents(
                const rapidjson::Value& v,
                const ComponentTemplateLib& componentTemplateLib);

    void resetSpan();

private:
    std::vector<Component> components_;
};

unsigned int CompositeObjectTemplate::numComponents() const
{
    return components_.size();
}

const Component& CompositeObjectTemplate::component(unsigned int i) const
{
    return components_[i];
}

const std::vector<Component>& CompositeObjectTemplate::components() const
{
    return components_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
