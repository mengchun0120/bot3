#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_map_navigator.h>

namespace mcdane {
namespace botlib {

MapNavigator::MapNavigator()
    : radius_(0.0f)
    , texture_(nullptr)
    , actions_(4)
{
}

void MapNavigator::init(float x,
                        float y,
                        float radius,
                        const commonlib::Texture *texture,
                        const std::vector<Action> &actions)
{
    Widget::init(x, y, 2.0f*radius, 2.0f*radius, true, true, true);
    radius_ = radius;
    texture_ = texture;
    actions_.
}

void MapNavigator::present() const
{
}

bool MapNavigator::containPos(float x, float y)
{
    float distX = x - pos_[0];
    float distY = y - pos_[1];
    return distX * distX + distY * distY <= radius_;
}

void MapNavigator::onLostFocus()
{
}

void MapNavigator::onPointerOut()
{
}

void MapNavigator::onPointerOver()
{
}

void MapNavigator::onPointerDown()
{
}

} // end of namespace botlib
} // end of namespace mcdane
