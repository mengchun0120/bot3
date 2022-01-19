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
    static void initConfig(const std::string& cfgFile);

    HPIndicator() = default;

    ~HPIndicator() = default;

    void reset(const commonlib::Vector2& pos,
               float hpPercent);

    void present() const;

    void shiftPos(const commonlib::Vector2& delta);

private:
    static void readColors(const std::string& cfgFile);

    static void validateColors();

    static void initSize();

    void setPos(const commonlib::Vector2& pos);

    void setHPPercent(float hpPercent);

    void resetColor(float hpPercent);

private:
    static std::vector<commonlib::Color> k_colors;
    static constexpr TextSize k_textSize = TextSize::TINY;
    static constexpr int k_hpLevelCount = 3;
    static float k_hpLevels[];
    static float k_halfHeight;

    commonlib::Vector2 pos_;
    std::string hpPercentStr_;
    commonlib::Color* color_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
