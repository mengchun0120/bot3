#ifndef INCLUDED_BOTLIB_ICON_H
#define INCLUDED_BOTLIB_ICON_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class IconTemplate;

class Icon {
public:
    Icon() = default;

    void init(const IconTemplate *t,
              const commonlib::Vector2 *p=nullptr);

    void present() const;

    void setPos(const commonlib::Vector2 &p);

private:
    const IconTemplate *t_;
    commonlib::Vector2 pos_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

