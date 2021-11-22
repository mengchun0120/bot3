#include <algorithm>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_composite_object.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

CompositeObject::CompositeObject()
    : GameObject()
{
}

void CompositeObject::init(const CompositeObjectTemplate* t,
                           float x,
                           float y,
                           float directionX,
                           float directionY)
{
    GameObject::init(t, x, y);
    direction_[0] = directionX;
    direction_[1] = directionY;
    initComponents();
}

void CompositeObject::init(const CompositeObjectTemplate* t,
                           const commonlib::Vector2& pos,
                           const commonlib::Vector2& direction)
{
    init(t, pos[0], pos[1], direction[0], direction[1]);
}

void CompositeObject::present() const
{
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        components_[i].present();
    }
}

void CompositeObject::setPos(float x,
                             float y)
{
    shiftPos(x - pos_[0], y - pos_[1]);
}

void CompositeObject::shiftPos(float deltaX,
                               float deltaY)
{
    GameObject::shiftPos(deltaX, deltaY);
    shiftComponents(deltaX, deltaY);
}

void CompositeObject::setDirection(float directionX,
                                   float directionY)
{
    direction_[0] = directionX;
    direction_[1] = directionY;
    repositionComponents();
}

void CompositeObject::initComponents()
{
    const CompositeObjectTemplate* t = getTemplate();

    components_.resize(t->numComponents());
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        components_[i].setTemplate(t->component(i).getTemplate());
    }

    repositionComponents();
}

void CompositeObject::repositionComponents()
{
    const CompositeObjectTemplate* t = getTemplate();

    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        const Component& c1 = t->component(i);
        Component& c2 = components_[i];

        Vector2 p = c1.pos();
        rotate(p[0], p[1], direction_[0], direction_[1]);
        c2.setPos(pos_ + p);

        Vector2 d = c1.direction();
        rotate(d[0], d[1], direction_[0], direction_[1]);
        c2.setDirection(d);
    }
}

void CompositeObject::shiftComponents(float deltaX,
                                      float deltaY)
{
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        components_[i].shiftPos(deltaX, deltaY);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

