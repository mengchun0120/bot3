#include <sstream>
#include <iomanip>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_string_utils.h>
#include <botlib_context.h>
#include <botlib_hp_indicator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void HPIndicator::reset(const commonlib::Vector2& pos,
                        float hpPercent)
{
    setHPPercent(hpPercent);
    setPos(pos);
}

void HPIndicator::present() const
{
    Graphics& g = Context::graphics();
    HPIndicatorConfig hpCfg = Context::hpIndicatorConfig();

    g.textSys().draw(g.simpleShader(), hpPercentStr_, pos_,
                     hpCfg.textSize(), color_);
}

void HPIndicator::shiftPos(const commonlib::Vector2& delta)
{
    pos_ += delta;
}

void HPIndicator::setPos(const commonlib::Vector2& pos)
{
    Graphics& g = Context::graphics();
    HPIndicatorConfig hpCfg = Context::hpIndicatorConfig();

    pos_[1] = pos[1] - hpCfg.halfHeight();

    float width = g.textSys().getWidth(hpPercentStr_, hpCfg.textSize());
    pos_[0] = pos[0] - width/2.0f;
}

void HPIndicator::setHPPercent(float hpPercent)
{
    if (hpPercent < 0.0f || hpPercent > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid hpPercent " + stringVal(hpPercent));
    }

    std::ostringstream oss;

    oss << std::fixed << std::setprecision(0) << (hpPercent * 100.0f) << '%';
    hpPercentStr_ = oss.str();

    resetColor(hpPercent);
}

void HPIndicator::resetColor(float hpPercent)
{
    HPIndicatorConfig hpCfg = Context::hpIndicatorConfig();
    color_ = hpCfg.color(hpPercent);
}

} // end of namespace botlib
} // end of namespace mcdane

