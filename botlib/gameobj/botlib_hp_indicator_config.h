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
    HPIndicatorConfig(Graphics& g,
                      const std::string& fileName);

    ~HPIndicatorConfig() = default;

    inline TextSize textSize() const;

    const commonlib::Color* color(float hpPercent) const;

    inline float halfHeight() const;

private:
    void init(Graphics& g,
              const std::string& fileName);

    void initSize(Graphics& g);

private:
    TextSize textSize_;
    std::vector<float> levels_;
    std::vector<commonlib::Color> colors_;
    float halfHeight_;
};

TextSize HPIndicatorConfig::textSize() const
{
    return textSize_;
}

float HPIndicatorConfig::halfHeight() const
{
    return halfHeight_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

