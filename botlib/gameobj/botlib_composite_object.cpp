#include <algorithm>
#include <sstream>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <commonlib_out_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_graphics.h>
#include <botlib_composite_object.h>
#include <botlib_player.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

CompositeObject::CompositeObject()
    : GameObject()
{
}

void CompositeObject::init(const CompositeObjectTemplate* t,
                           const commonlib::Vector2& pos1,
                           const commonlib::Vector2& direction1)
{
    GameObject::init(t, pos1);
    direction_ = direction1;
    initComponents();
}

void CompositeObject::present() const
{
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        components_[i].present();
    }
}

void CompositeObject::shiftPos(const Vector2& delta)
{
    GameObject::shiftPos(delta);
    shiftComponents(delta);
}

void CompositeObject::setDirection(const Vector2& direction1)
{
    direction_ = direction1;
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

void CompositeObject::shiftComponents(const Vector2& delta)
{
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        components_[i].shiftPos(delta);
    }
}

std::string CompositeObject::toString() const
{
    std::ostringstream oss;

    oss << "CompositeObject(" << this
        << ", direction=" << direction_
        << ", components=" << components_
        << ", Base=" << GameObject::toString()
        << ")";

    return oss.str();
}

rapidjson::Value CompositeObject::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "CompositeObject", allocator);
    v.AddMember("direction", jsonVal(direction_, allocator), allocator);
    v.AddMember("components", jsonVal(components_, allocator), allocator);
    v.AddMember("base", GameObject::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

