#ifndef INCLUDED_BOTLIB_HP_INDICATOR_H
#define INCLUDED_BOTLIB_HP_INDICATOR_H

#include <string>
#include <commonlib_vector.h>
#include <commonlib_color.h>
#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

class HPIndicator {
public:
    HPIndicator() = default;

    ~HPIndicator() = default;

    void reset(const commonlib::Vector2 &pos,
               float hpPercent);

    void present() const;

    void shiftPos(const commonlib::Vector2 &delta);

private:
    void setPos(const commonlib::Vector2 &pos);

    void setHPPercent(float hpPercent);
private:
    commonlib::Vector2 pos_;
    std::string hpPercentStr_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

