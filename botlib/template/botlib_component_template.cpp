#include <cmath>
#include <commonlib_exception.h>
#include <botlib_component_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentTemplate::ComponentTemplate(const Texture* texture,
                                     const Rectangle* rect)
{
    init(texture, rect);
}

void ComponentTemplate::init(const commonlib::Texture* texture,
                             const Rectangle* rect)
{
    if (!texture)
    {
        THROW_EXCEPT(InvalidArgumentException, "texture is null");
    }

    if (!rect)
    {
        THROW_EXCEPT(InvalidArgumentException, "rect is null");
    }

    texture_ = texture;
    rect_ = rect;
    span_ = static_cast<float>(sqrt(rect_->width() * rect_->width() +
                                    rect_->height() * rect_->height()) / 2.0);
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::ComponentTemplate& t)
{
    os << "ComponentTemplate(" << &t
       << ", texture=" << *(t.texture())
       << ", rect=" << *(t.rect())
       << ")";

    return os;
}

} // end of namespace std


