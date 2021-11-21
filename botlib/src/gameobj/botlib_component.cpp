#include <commonlib_exception.h>
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
                     float x,
                     float y,
                     float directionX,
                     float directionY)
{
    if (!t_)
    {
        THROW_EXCEPT(InvalidArgumentException, "ComponentTemplate is null");
    }

    t_ = t;
    pos_[0] = x;
    pos_[1] = y;
    direction_[0] = directionX;
    direction_[1] = directionY;
}

void Component::init(const ComponentTemplate* t,
                     const commonlib::Vector2& pos,
                     const commonlib::Vector2& direction)
{
    init(t, pos[0], pos[1], direction[0], direction[1]);
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

void Component::setPos(float x,
                       float y)
{
    pos_[0] = x;
    pos_[1] = y;
}

void Component::setPos(const commonlib::Vector2& p)
{
    pos_ = p;
}

void Component::shiftPos(float deltaX,
                         float deltaY)
{
    pos_[0] += deltaX;
    pos_[1] += deltaY;
}

void Component::setDirection(float directionX,
                             float directionY)
{
    direction_[0] = directionX;
    direction_[1] = directionY;
}

void Component::setDirection(const commonlib::Vector2& d)
{
    direction_ = d;
}

void Component::present() const
{
    SimpleShaderProgram& program = Graphics::simpleShader();

    t_->rect()->draw(program, &pos_, &direction_, nullptr, nullptr,
                     t_->texture()->id(), nullptr);
}

} // end of namespace botlib
} // end of namespace mcdane

