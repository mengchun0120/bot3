#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <botlib_graphics.h>
#include <botlib_component.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Component::Component()
    : t_(nullptr)
{
}

Component::Component(const Component& other)
    : t_(other.t_)
    , pos_(other.pos_)
    , direction_(other.direction_)
{
}

void Component::init(const ComponentTemplate* t,
                     const commonlib::Vector2& pos1,
                     const commonlib::Vector2& direction1)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "ComponentTemplate is null");
    }

    t_ = t;
    pos_ = pos1;
    direction_ = direction1;
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

void Component::setPos(const commonlib::Vector2& pos1)
{
    pos_ = pos1;
}

void Component::shiftPos(const commonlib::Vector2& delta)
{
    pos_ += delta;
}

void Component::setDirection(const commonlib::Vector2& direction1)
{
    direction_ = direction1;
}

void Component::present() const
{
    SimpleShaderProgram& program = Graphics::simpleShader();

    t_->rect()->draw(program, &pos_, &direction_, nullptr, nullptr,
                     t_->texture()->id(), nullptr);
}

rapidjson::Value Component::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "component", allocator);
    v.AddMember("template", t_->id(), allocator);
    v.AddMember("pos", jsonVal(pos_, allocator), allocator);
    v.AddMember("direction", jsonVal(direction_, allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

