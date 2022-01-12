#include <cmath>
#include <commonlib_exception.h>
#include <botlib_component_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentTemplate::ComponentTemplate(const Texture* texture,
                                     const Rectangle* rect)
    : texture_(texture)
    , rect_(rect)
{
    if (!texture_)
    {
        THROW_EXCEPT(InvalidArgumentException, "texture is null");
    }

    if (!rect_)
    {
        THROW_EXCEPT(InvalidArgumentException, "rect is null");
    }

    span_ = static_cast<float>(sqrt(rect_->width() * rect_->width() +
                                    rect_->height() * rect_->height()) / 2.0);
}

} // end of namespace botlib
} // end of namespace mcdane

