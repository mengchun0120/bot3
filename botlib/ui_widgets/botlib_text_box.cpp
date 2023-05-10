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
    Widget::init(x, y, true, false);

}

void TextBox::setPos(float x, float y)
{
}

void TextBox::shiftPos(float dx, float dy)
{
}

void TextBox::present() const
{
}

#ifdef DESKTOP_APP
void TextBox::onKey(const commonlib::KeyEvent &e)
{
}
#endif

void TextBox::onLostFocus()
{
}

void TextBox::onPointerDown(float x, float y)
{
}

bool TextBox::containPos(float x, float y) const
{
    return false;
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
}

void TextBox::initText(int maxTextLen)
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    text_.resize(maxTextLen);
    textLen_ = 0;
    textSize_ = textSize1;
    firstIndex_ = 0;
    textPos_.init{
        pos_[0] + cfg.leftMargin(),
        pos_[1] + box_.height() - cfg.topMargin() - cfg.textHeight()
    };
}

void TextBox::initCaret()
{
    const TextBoxConfig &cfg = Context::textBoxConfig();

    caretIndex_ = 0;
    caretPos_.init{
        pos_[0] + cfg.leftMargin() + cfg.caretWidth() / 2.0f,
        pos_[1] + box_.height() - cfg.topMargin() - cfg.caretHeight() / 2.0f
    };
}

} // end of namespace botlib
} // end of namespace mcdane
