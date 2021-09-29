#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_graphics.h>
#include <botlib_label.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Color Label::k_defaultTextColor;
Color Label::k_defaultBackColor;
Color Label::k_defaultBorderColor;

void Label::initConfig(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(k_defaultTextColor, {"defaultTextColor"}, true,
                  nonempty(k_defaultTextColor)),
        jsonParam(k_defaultBackColor, {"defaultBackColor"}, true,
                  nonempty(k_defaultBackColor)),
        jsonParam(k_defaultBorderColor, {"defaultBorderColor"}, true,
                  nonempty(k_defaultBorderColor))
    };

    parse(params, doc);
}

Label::Label(float x,
             float y,
             float width,
             float height,
             const std::string text,
             TextSize textSize,
             HAlign halign,
             VAlign valign,
             const Color& textColor,
             const Color* backColor,
             const Color* borderColor,
             bool visible)
{
    init(x, y, width, height, text, textSize, halign, valign,
         textColor, backColor, borderColor, visible);
}

Label::~Label()
{
    delete backColor_;
    delete borderColor_;
}

void Label::init(float x,
                 float y,
                 float width,
                 float height,
                 const std::string text,
                 TextSize textSize,
                 HAlign halign,
                 VAlign valign,
                 const Color& textColor,
                 const Color* backColor,
                 const Color* borderColor,
                 bool visible)
{
    if (!isValidTextSize(textSize))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid textSize");
    }

    if (!isValidHAlign(halign))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid halign");
    }

    if (!isValidVAlign(valign))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid valign");
    }

    Widget::init(x, y, width, height, visible, false, false);
    text_ = text;
    textSize_ = textSize;
    halign_ = halign;
    valign_ = valign;
    updateTextPos();
    textColor_ = textColor;

    if (backColor)
    {
        backColor_ = new Color(*backColor);
    }
    else
    {
        backColor_ = nullptr;
    }

    if (borderColor)
    {
        borderColor_ = new Color(*borderColor);
    }
    else
    {
        borderColor_ = nullptr;
    }
}

void Label::setPos(float x,
                   float y)
{
    Widget::setPos(x, y);
    updateTextPos();
}

void Label::shiftPos(float dx,
                     float dy)
{
    Widget::shiftPos(dx, dy);
    textPos_[0] += dx;
    textPos_[1] += dy;
}

void Label::present() const
{
    Graphics& g = Graphics::getInstance();

    rect_.draw(g.simpleShader(), &pos_, nullptr, backColor_,
               borderColor_, 0, nullptr);
    if (text_.size() > 0)
    {
        g.textSys().draw(g.simpleShader(), text_, textPos_,
                         textSize_, &textColor_);
    }
}

void Label::setText(const std::string& text)
{
    text_ = text;
    textPos_[0] = calculateTextPosX();
}

void Label::setTextSize(TextSize textSize)
{
    if (!isValidTextSize(textSize))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid textSize");
    }

    if (textSize_ == textSize)
    {
        return;
    }

    textSize_ = textSize;
    updateTextPos();
}

void Label::setHAlign(HAlign halign)
{
    if (!isValidHAlign(halign))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid halign");
    }

    if (halign_ == halign)
    {
        return;
    }

    halign_ = halign;
    textPos_[0] = calculateTextPosX();
}

void Label::setVAlign(VAlign valign)
{
    if (!isValidVAlign(valign))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid valign");
    }

    if (valign_ == valign)
    {
        return;
    }

    valign_ = valign;
    textPos_[1] = calculateTextPosY();
}

void Label::updateTextPos()
{
    textPos_[0] = calculateTextPosX();
    textPos_[1] = calculateTextPosY();
}

float Label::calculateTextPosX()
{
    TextSystem& textSys = Graphics::getInstance().textSys();
    float x;

    switch(halign_)
    {
        case HAlign::LEFT:
        {
            x = pos_[0] - width() / 2.0f;
            break;
        }
        case HAlign::MIDDLE:
        {
            float w = textSys.getWidth(text_, textSize_);
            x = pos_[0] - w / 2.0f;
            break;
        }
        case HAlign::RIGHT:
        {
            float w = textSys.getWidth(text_, textSize_);
            x = pos_[0] + width()/2.0f - w;
            break;
        }
    }

    return x;
}

float Label::calculateTextPosY()
{
    TextSystem& textSys = Graphics::getInstance().textSys();
    float y;

    switch(valign_)
    {
        case VAlign::TOP:
        {
            float h = textSys.getHeight(textSize_);
            y = pos_[1] + height()/2.0f - h;
            break;
        }
        case VAlign::MIDDLE:
        {
            float h = textSys.getHeight(textSize_);
            y = pos_[1] - h / 2.0f;
            break;
        }
        case VAlign::BOTTOM:
        {
            y = pos_[1] - height() / 2.0f;
            break;
        }
    }

    return y;
}

} // end of namespace botlib
} // end of namespace mcdane

