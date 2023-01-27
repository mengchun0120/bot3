#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_label.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Label::Label(float x,
             float y,
             float width,
             float height,
             const std::string text,
             TextSize textSize,
             HAlign halign,
             VAlign valign,
             const Color* textColor,
             const Color* backColor,
             const Color* borderColor,
             bool visible)
{
    init(x, y, width, height, text, textSize, halign, valign,
         textColor, backColor, borderColor, visible);
}

void Label::init(float x,
                 float y,
                 float width,
                 float height,
                 const std::string text,
                 TextSize textSize,
                 HAlign halign,
                 VAlign valign,
                 const Color* textColor,
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
    initColors(textColor, backColor, borderColor);
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
    Graphics& g = Context::graphics();
    SimpleShaderProgram& program = g.simpleShader();
    const TextSystem& textSys = g.textSys();

    program.setAlpha(1.0f);

    rect_.draw(program, &pos_, nullptr, &backColor_, &borderColor_, 0, nullptr);
    if (text_.size() > 0)
    {
        textSys.draw(program, text_, textPos_, textSize_, &textColor_);
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

void Label::initColors(const Color* textColor,
                       const Color* backColor,
                       const Color* borderColor)
{
    const LabelConfig& cfg = Context::labelConfig();

    textColor_ = textColor ? *textColor : cfg.defaultTextColor();
    backColor_ = backColor ? *backColor : cfg.defaultBackColor();
    borderColor_ = borderColor ? *borderColor : cfg.defaultBorderColor();
}

float Label::calculateTextPosX()
{
    const TextSystem& textSys = Context::graphics().textSys();
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
    const TextSystem& textSys = Context::graphics().textSys();
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

