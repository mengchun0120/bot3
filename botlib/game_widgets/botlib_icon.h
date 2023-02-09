#ifndef INCLUDED_BOTLIB_ICON_H
#define INCLUDED_BOTLIB_ICON_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class IconTemplate;

class Icon {
public:
    Icon() = default;

    void init(const IconTemplate* t);

    void present(const commonlib::Vector2& pos) const;

private:
    const IconTemplate* t_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

