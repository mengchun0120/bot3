#include <cmath>
#include <algorithm>
#include <iostream>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_text_box.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void TextBox::init(float x,
                   float y,
                   float width,
                   float height,
                   int maxTextLen)
{
    Widget::init(x, y, true, true);
    initBox(width, height);
    initText(maxTextLen);
    initCaret();
}

void TextBox::setPos(float x, float y)
{
    shiftPos(x - pos_[0], y - pos_[1]);
}

void TextBox::shiftPos(float dx, float dy)
{
    Vector2 d{dx, dy};

    Widget::shiftPos(dx, dy);
    boxPos_ += d;
    textPos_ += d;
    caretPos_ += d;
}

void TextBox::present() const
{
    const TextBoxConfig &cfg = Context::textBoxConfig();
    Graphics &g = Context::graphics();
    SimpleShaderProgram &program = g.simpleShader();

    box_.draw(program, &boxPos_, nullptr, &cfg.backColor(), &cfg.borderColor(),
              0, nullptr);

    if (visibleTextLen_ > 0)
    {
        g.textSys().draw(program, visibleTextBegin(), visibleTextEnd(),
                         textPos_, cfg.textSize(), &cfg.textColor());
    }

    if (showCaret_ && caretVisible_)
    {
        cfg.caretRect().draw(program, &caretPos_, nullptr, &cfg.caretColor(),
                             nullptr, 0, nullptr);
    }
}

#ifdef DESKTOP_APP
void TextBox::onKey(const commonlib::KeyEvent &e)
{
    if (e.action_ != GLFW_PRESS && e.action_ != GLFW_REPEAT)
    {
        return;
    }

    std::pair<int, bool> res = translate(e);

    if (res.second)
    {
        onPrintableKey(static_cast<char>(res.first));
    }
    else
    {
        onUnprintableKey(e.key_);
    }
}

#endif

void TextBox::onLostFocus()
{
    showCaret_ = false;
}

void TextBox::onPointerDown(float x, float y)
{
    showCaret_ = true;
    caretVisible_ = true;
    blinkDuration_ = 0.0f;
}

void TextBox::update(float timeDelta)
{
    if (!showCaret_)
    {
        return;
    }

    const TextBoxConfig &cfg = Context::textBoxConfig();

    blinkDuration_ += timeDelta;
    if (blinkDuration_ >= cfg.blinkTime())
    {
        caretVisible_ = !caretVisible_;
        blinkDuration_ = 0.0f;
    }
}

bool TextBox::containPos(float x, float y) const
{
    return fabs(x - boxPos_[0]) <= box_.width() / 2.0f &&
           fabs(y - boxPos_[1]) <= box_.height() / 2.0f;
}

void TextBox::setText(const std::string &s)
{
}

void TextBox::initBox(float width, float height)
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    if (width < cfg.minWidth())
    {
        width = cfg.minWidth();
    }

    if (height < cfg.minHeight())
    {
        height = cfg.minHeight();
    }

    box_.init(width, height);
    boxPos_.init({
        pos_[0] + width / 2.0f,
        pos_[1] + height / 2.0f
    });
}

void TextBox::initText(int maxTextLen)
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    text_.resize(maxTextLen);
    textLen_ = 0;
    visibleTextStartIndex_ = 0;
    visibleTextLen_ = 0;
    textPos_.init({
        pos_[0] + cfg.leftMargin(),
        pos_[1] + box_.height() - cfg.topMargin() - cfg.textHeight()
    });
}

void TextBox::initCaret()
{
    blinkDuration_ = 0.0f;
    caretIndex_ = 0;
    showCaret_ = false;
    caretPos_.init({firstCaretX(), caretY()});
}

void TextBox::onPrintableKey(char ch)
{
    if (textLen_ >= static_cast<int>(text_.size()))
    {
        return;
    }

    for (int i = textLen_ - 1; i >= caretIndex_; --i)
    {
        text_[i + 1] = text_[i];
    }

    text_[caretIndex_] = ch;
    ++textLen_;
    ++caretIndex_;

    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();

    caretPos_[0] += textSys.getWidth(ch, cfg.textSize());
    ++visibleTextLen_;

    recalibrateCaretPos();
    recalibrateVisibleTextLen();
}

void TextBox::onUnprintableKey(int key)
{
    switch (key)
    {
        case GLFW_KEY_LEFT:
            onKeyLeft();
            break;
        case GLFW_KEY_RIGHT:
            onKeyRight();
            break;
        case GLFW_KEY_BACKSPACE:
            onKeyBackspace();
            break;
        case GLFW_KEY_DELETE:
            onKeyDelete();
            break;
        case GLFW_KEY_HOME:
            onKeyHome();
            break;
        case GLFW_KEY_END:
            onKeyEnd();
            break;
        default:
            break;
    }
}

void TextBox::onKeyLeft()
{
    if (caretIndex_ == 0)
    {
        return;
    }

    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();

    --caretIndex_;
    caretPos_[0] -= textSys.getWidth(text_[caretIndex_], cfg.textSize());

    recalibrateCaretPos();
    recalibrateVisibleTextLen();
}

void TextBox::onKeyRight()
{
    if (caretIndex_ >= textLen_)
    {
        return;
    }

    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();

    caretPos_[0] += textSys.getWidth(text_[caretIndex_], cfg.textSize());
    ++caretIndex_;

    recalibrateCaretPos();
    recalibrateVisibleTextLen();
}

void TextBox::onKeyBackspace()
{
    if (caretIndex_ == 0)
    {
        return;
    }

    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();

    caretPos_[0] -= textSys.getWidth(text_[caretIndex_ - 1], cfg.textSize());

    for (int i = caretIndex_; i < textLen_; ++i)
    {
        text_[i-1] = text_[i];
    }

    --textLen_;
    --caretIndex_;

    recalibrateCaretPos();
    recalibrateVisibleTextLen();
}

void TextBox::onKeyDelete()
{
    if (caretIndex_ == textLen_)
    {
        return;
    }

    for (int i = caretIndex_ + 1; i < textLen_; ++i)
    {
        text_[i-1] = text_[i];
    }

    --textLen_;

    recalibrateVisibleTextLen();
}

void TextBox::onKeyHome()
{
    caretIndex_ = 0;
    caretPos_[0] = firstCaretX();
    visibleTextStartIndex_ = 0;

    recalibrateVisibleTextLen();
}

void TextBox::onKeyEnd()
{
    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();

    caretPos_[0] += textSys.getWidth(text_.data() + caretIndex_,
                                     text_.data() + textLen_, cfg.textSize());
    caretIndex_ = textLen_;
    visibleTextLen_ = textLen_ - visibleTextStartIndex_;

    recalibrateCaretPos();
}

void TextBox::recalibrateCaretPos()
{
    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();
    float boxRight = pos_[0] + box_.width();

    if (caretPos_[0] > boxRight)
    {
        float w;

        while (caretPos_[0] > boxRight)
        {
            w = textSys.getWidth(text_[visibleTextStartIndex_], cfg.textSize());
            caretPos_[0] -= w;
            ++visibleTextStartIndex_;
            --visibleTextLen_;
        }
    }
    else if (caretPos_[0] < textPos_[0])
    {
        visibleTextStartIndex_ = caretIndex_;
        caretPos_[0] = textPos_[0];
    }
}

void TextBox::recalibrateVisibleTextLen()
{
    const TextBoxConfig &cfg = Context::textBoxConfig();
    const TextSystem &textSys = Context::graphics().textSys();
    float maxVisibleWidth = box_.width() - cfg.leftMargin();
    float visibleWidth, charWidth;
    int lastVisibleIndex;

    visibleTextLen_ = textLen_ - visibleTextStartIndex_;
    lastVisibleIndex = visibleTextStartIndex_ + visibleTextLen_ - 1;
    visibleWidth = textSys.getWidth(visibleTextBegin(), visibleTextEnd(),
                                    cfg.textSize());

    while (visibleWidth >= maxVisibleWidth)
    {
        charWidth = textSys.getWidth(text_[lastVisibleIndex], cfg.textSize());
        visibleWidth -= charWidth;
        --visibleTextLen_;
        --lastVisibleIndex;
    }
}

float TextBox::firstCaretX() const
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    return pos_[0] + cfg.leftMargin();
}

float TextBox::caretY() const
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    return pos_[1] + box_.height() - cfg.topMargin() - cfg.caretHeight() / 2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane
