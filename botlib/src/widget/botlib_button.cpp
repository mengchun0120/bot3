#include <botlib_button.h>

namespace mcdane {
namespace botlib {

Button::Button()
    : textColor_(nullptr)
    , state_(STATE_NORMAL)
    , textSize_(TEXT_SIZE_INVALID)
{
}

void Button::init(float x,
                  float y,
                  float z,
                  float width,
                  float height,
                  const std::string& text,
                  TextSize textSize,
                  bool visible,
                  bool acceptInput)
{
    if (!isValidTextSize(textSize))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid textSize");
    }

    init(x, y, z, width, height, visible, acceptInput, true);
    setText(text);
}

void Button::present(SimpleShaderProgram& shader,
                     TextSystem& textSys) const
{
    rect_.draw(shader, z_, pos_, nullptr, nullptr, nullptr, 
}

void Button::setText(const std::string &text)
{
}

void Button::setActionFunc(const ActionFunc &actionFunc)
{
}

void Button::setPos(float x,
                    float y,
                    float z)
{
}

void Button::shiftPos(float dx,
                      float dy)
{
}

void Button::process(const KeyEvent &event)
{
}

void Button::process(const MouseMoveEvent &event)
{
}

void Button::process(const MouseButtonEvent &event)
{
}

void Button::onMouseOut()
{
}

} // end of namespace botlib
} // end of namespace mcdane

