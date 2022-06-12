#ifndef INCLUDED_BOTLIB_HP_INDICATOR_CONFIG_H
#define INCLUDED_BOTLIB_HP_INDICATOR_CONFIG_H

#include <string>
#include <vector>
#include <commonlib_color.h>
#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

class Graphics;

class HPIndicatorConfig {
public:
    HPIndicatorConfig() = default;

    ~HPIndicatorConfig() = default;

    void init(const std::string& fileName);

    inline TextSize textSize() const;

    inline const commonlib::Color& color() const;

    inline float halfHeight() const;

private:

    void initSize();

private:
    TextSize textSize_;
    commonlib::Color color_;
    float halfHeight_;
};

TextSize HPIndicatorConfig::textSize() const
{
    return textSize_;
}

const commonlib::Color& HPIndicatorConfig::color() const
{
    return color_;
}

float HPIndicatorConfig::halfHeight() const
{
    return halfHeight_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

