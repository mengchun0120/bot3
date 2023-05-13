#include <cmath>
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
    std::cout << e.key_ << ' ' << e.mods_ << std::endl;
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
    const TextBoxConfig &cfg = Context::textBoxConfig();

    blinkDuration_ = 0.0f;
    caretIndex_ = 0;
    showCaret_ = false;
    caretPos_.init({
        pos_[0] + cfg.leftMargin() + cfg.caretWidth() / 2.0f,
        pos_[1] + box_.height() - cfg.topMargin() - cfg.caretHeight() / 2.0f
    });
}

} // end of namespace botlib
} // end of namespace mcdane
