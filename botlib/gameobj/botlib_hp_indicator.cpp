#include <sstream>
#include <iomanip>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_string_utils.h>
#include <botlib_graphics.h>
#include <botlib_hp_indicator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::vector<commonlib::Color> HPIndicator::k_colors;

float HPIndicator::k_hpLevels[] = {
    0.4f, 0.15f, 0.0f
};

float HPIndicator::k_halfHeight;

void HPIndicator::initConfig(const std::string& cfgFile)
{
    readColors(cfgFile);
    validateColors();
    initSize();
}

void HPIndicator::readColors(const std::string& cfgFile)
{
    rapidjson::Document doc;
    readJson(doc, cfgFile);

    std::vector<JsonParamPtr> params{
        jsonParam(k_colors, "colors")
    };

    parse(params, doc);
}

void HPIndicator::validateColors()
{
    if (k_colors.size() != k_hpLevelCount)
    {
        THROW_EXCEPT(ParseException, "Invalid size for HPIndicator::k_colors");
    }
}

void HPIndicator::initSize()
{
    k_halfHeight = Graphics::textSys().getHeight(k_textSize) / 2.0f;
}

void HPIndicator::reset(const commonlib::Vector2& pos,
                        float hpPercent)
{
    setHPPercent(hpPercent);
    setPos(pos);
}

void HPIndicator::present() const
{
    Graphics::textSys().draw(Graphics::simpleShader(), hpPercentStr_, pos_,
                             k_textSize, color_);
}

void HPIndicator::shiftPos(const commonlib::Vector2& delta)
{
    pos_ += delta;
}

void HPIndicator::setPos(const commonlib::Vector2& pos)
{
    pos_[1] = pos[1] - k_halfHeight;

    float width = Graphics::textSys().getWidth(hpPercentStr_, k_textSize);
    pos_[0] = pos[0] - width/2.0f;
}

void HPIndicator::setHPPercent(float hpPercent)
{
    if (hpPercent < 0.0f || hpPercent > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid hpPercent " + toString(hpPercent));
    }

    std::ostringstream oss;

    oss << std::fixed << std::setprecision(0) << (hpPercent * 100.0f) << '%';
    hpPercentStr_ = oss.str();

    resetColor(hpPercent);
}

void HPIndicator::resetColor(float hpPercent)
{
    int level;
    for (level = 0; level < k_hpLevelCount; ++level)
    {
        if (hpPercent >= k_hpLevels[level])
        {
            break;
        }
    }

    color_ = &k_colors[level];
}

} // end of namespace botlib
} // end of namespace mcdane

