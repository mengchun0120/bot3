#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_graphics.h>
#include <botlib_button.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::vector<Color> Button::k_textColors;
Texture Button::k_texture;

void Button::initConfig(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::string textureFile;
    std::vector<JsonParamPtr> params{
        jsonParam(k_textColors, {"textColor"}, true, nonempty(k_textColors)),
        jsonParam(textureFile, {"textureFile"}, true, nonempty(textureFile))
    };

    parse(params, doc);

    validateTextColor();
    k_texture.init(textureFile);
}

void Button::validateTextColor()
{
    if (k_textColors.size() != STATE_COUNT)
    {
        THROW_EXCEPT(MyException, "Size of textColor is invalid");
    }

    for (std::size_t i = 0; i < k_textColors.size(); ++i)
    {
        if (!isValidColor(k_textColors[i]))
        {
            THROW_EXCEPT(MyException,
                         "k_textColors[" + std::to_string(i) + "] is invalid");
        }
    }
}

Button::Button()
    : state_(STATE_NORMAL)
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

    Widget::init(x, y, z, width, height, visible, acceptInput, true);
    setText(text);
}

void Button::present() const
{
    if (!visible_)
    {
        return;
    }

    Graphics& g = Graphics::getInstance();

    rect_.draw(g.simpleShader(), z_, &pos_, nullptr, nullptr, nullptr,
               k_texture.id(), nullptr);

    g.textSys().draw(g.simpleShader(), text_, textPos_, z_, textSize_,
                     &k_textColors[state_]);
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

void Button::setPos(float x,
                    float y,
                    float z)
{
    Widget::setPos(x, y, z);
    resetTextPos();
}

void Button::shiftPos(float dx,
                      float dy)
{
    Widget::shiftPos(dx, dy);
    textPos_[0] += dx;
    textPos_[1] += dy;
}

#ifdef DESKTOP_APP

void Button::process(const KeyEvent &event)
{
    if (!acceptInput_)
    {
        return;
    }

    switch (event.key_)
    {
        case GLFW_KEY_ENTER:
            if (action_ && event.action_ == GLFW_PRESS)
            {
                action_();
            }
            break;
        default:
            break;
    }
}

void Button::process(const MouseMoveEvent &event)
{
    if (!acceptInput_)
    {
        return;
    }

    state_ = STATE_HOVER;
}

void Button::process(const MouseButtonEvent &event)
{
    if (!acceptInput_)
    {
        return;
    }

    if (event.button_ == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (event.action_ == GLFW_PRESS)
        {
            state_ = STATE_PRESSED;
        }
        else if (event.action_ == GLFW_RELEASE && action_)
        {
            action_();
        }
    }
}

void Button::onMouseOut()
{
    state_ = STATE_NORMAL;
}

#endif

void Button::resetTextPos()
{
    Graphics& g = Graphics::getInstance();
    commonlib::Vector2 sz = g.textSys().getSize(text_, textSize_);

    float marginX = (rect_.width() - sz[0]) / 2.0f;
    float marginY = (rect_.height() - sz[1]) / 2.0f;

    textPos_[0] = pos_[0] + marginX;
    textPos_[1] = pos_[1] + marginY;
}

} // end of namespace botlib
} // end of namespace mcdane

