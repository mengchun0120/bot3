#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_context.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Button::Button()
    : state_(STATE_NORMAL)
    , textSize_(TextSize::INVALID)
{
}

Button::Button(float x,
               float y,
               float width,
               float height,
               const std::string &text,
               TextSize textSize,
               bool visible,
               bool acceptInput)
{
    init(x, y, width, height, text, textSize, visible, acceptInput);
}

void Button::init(float x,
                  float y,
                  float width,
                  float height,
                  const std::string &text,
                  TextSize textSize,
                  bool visible,
                  bool acceptInput)
{
    if (!isValidTextSize(textSize))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid textSize");
    }

    text_ = text;
    textSize_ = textSize;
    state_ = STATE_NORMAL;
    RectangularWidget::init(x, y, width, height, visible, acceptInput, true);
    resetTextPos();

    LOG_INFO << "Button " << text_ << " " << pos_ << LOG_END;
}

void Button::present() const
{
    if (!visible_)
    {
        return;
    }

    Graphics &g = Context::graphics();
    SimpleShaderProgram &program = g.simpleShader();
    const TextSystem &textSys = g.textSys();
    const ButtonConfig &cfg = Context::buttonConfig();

    program.setAlpha(1.0f);

    rect_.draw(program, &pos_, nullptr, nullptr, nullptr,
               cfg.texture().id(), nullptr);

    textSys.draw(program, text_, textPos_, textSize_, cfg.textColor(state_));
}

void Button::setText(const std::string &text)
{
    text_ = text;
    resetTextPos();
}

void Button::setActionFunc(const ActionFunc &actionFunc)
{
    action_ = actionFunc;
}

void Button::setPos(float x, float y)
{
    RectangularWidget::setPos(x, y);
    resetTextPos();
}

void Button::shiftPos(float dx, float dy)
{
    RectangularWidget::shiftPos(dx, dy);
    textPos_[0] += dx;
    textPos_[1] += dy;
}

#ifdef DESKTOP_APP
void Button::onKey(const commonlib::KeyEvent &e)
{
    if (!acceptInput_)
    {
        return;
    }

    if (e.key_ == GLFW_KEY_ENTER && e.action_ == GLFW_PRESS && action_)
    {
        action_();
    }
}
#endif

void Button::onPointerOut()
{
    state_ = STATE_NORMAL;
}

void Button::onPointerOver()
{
    if (!acceptInput_)
    {
        return;
    }

    state_ = STATE_HOVER;
}

void Button::onPointerDown()
{
    if (!acceptInput_)
    {
        return;
    }

    state_ = STATE_NORMAL;

    if (action_)
    {
        action_();
    }
}

void Button::resetTextPos()
{
    const TextSystem &textSys = Context::graphics().textSys();
    commonlib::Vector2 sz = textSys.getSize(text_, textSize_);

    textPos_[0] = pos_[0] - sz[0]/2.0f;
    textPos_[1] = pos_[1] - sz[1]/2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

