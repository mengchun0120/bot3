#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_component_template.h>
#include <botlib_context.h>
#include <botlib_component.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Component::Component()
    : t_(nullptr)
{
}

Component::Component(const rapidjson::Value& v,
                     const ComponentTemplateLib& componentTemplateLib)
{
    init(v, componentTemplateLib);
}

Component::Component(const Component& other)
    : t_(other.t_)
    , pos_(other.pos_)
    , direction_(other.direction_)
{
}

void Component::init(const rapidjson::Value& v,
                     const ComponentTemplateLib& componentTemplateLib)
{
    std::string templateName;
    std::vector<JsonParamPtr> params{
        jsonParam(templateName, "template", true, k_nonEmptyStrV),
        jsonParam(pos_, "pos"),
        jsonParam(direction_, "direction")
    };

    parse(params, v);

    t_ = componentTemplateLib.search(templateName);
    if (!t_)
    {
        THROW_EXCEPT(ParseException, "Failed to find template " + templateName);
    }

    if (t_->type() == ComponentType::GUN)
    {
        resetFirePos();
    }
}

Component& Component::operator=(const Component& other)
{
    t_ = other.t_;
    pos_ = other.pos_;
    direction_ = other.direction_;
    return *this;
}

void Component::setTemplate(const ComponentTemplate* t)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "ComponentTemplate is null");
    }

    t_ = t;
}

void Component::setPos(const commonlib::Vector2& p)
{
    shiftPos(p - pos_);
}

void Component::shiftPos(const commonlib::Vector2& delta)
{
    pos_ += delta;
    firePos_ += delta;
}

void Component::setDirection(const commonlib::Vector2& direction1)
{
    direction_ = direction1;
    resetFirePos();
}

void Component::present() const
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    t_->rect()->draw(program, &pos_, &direction_, nullptr, nullptr,
                     t_->texture()->id(), nullptr);
}

void Component::resetFirePos()
{
    Vector2 p = t_->firePos();

    rotate(p[0], p[1], direction_[0], direction_[1]);
    firePos_ = pos_ + p;
}

} // end of namespace botlib
} // end of namespace mcdane

