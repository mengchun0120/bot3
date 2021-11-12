#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_graphics.h>
#include <botlib_button.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::vector<Color> Button::k_textColors;
Texture Button::k_texture;

void Button::initConfig(const std::string& configFile,
                        const std::string& picDir)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::string textureFile;
    std::vector<JsonParamPtr> params{
        jsonParam(k_textColors, {"textColor"}),
        jsonParam(textureFile, {"texture"}, true, k_nonEmptyStrV)
    };

    parse(params, doc);

    validateTextColor();

    textureFile = constructPath({picDir, textureFile});
    k_texture.init(textureFile);

    LOG_INFO << "Button::initConfig finished successfully" << LOG_END;
}

void Button::validateTextColor()
{
    if (k_textColors.size() != STATE_COUNT)
    {
        THROW_EXCEPT(MyException, "Size of textColor is invalid");
    }
}

Button::Button()
    : state_(STATE_NORMAL)
    , textSize_(TextSize::INVALID)
{
}

Button::Button(float x,
               float y,
               float width,
               float height,
               const std::string& text,
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
                  const std::string& text,
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
    Widget::init(x, y, width, height, visible, acceptInput, true);
    resetTextPos();
}

void Button::present() const
{
    if (!visible_)
    {
        return;
    }

    Graphics& g = Graphics::getInstance();

    rect_.draw(g.simpleShader(), &pos_, nullptr, nullptr, nullptr,
               k_texture.id(), nullptr);

    g.textSys().draw(g.simpleShader(), text_, textPos_, textSize_,
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
                    float y)
{
    Widget::setPos(x, y);
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

    textPos_[0] = pos_[0] - sz[0]/2.0f;
    textPos_[1] = pos_[1] - sz[1]/2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

