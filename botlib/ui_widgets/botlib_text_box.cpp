#include <commonlib_log.h>
#include <botlib_text_box.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void TextBox::init(float x,
          float y,
          float width,
          float height,
          TextSize textSize1=TextSize::MEDIUM,
          int maxTextLen=k_defaultMaxTexLen)
{
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

void setText(const std::string &s)
{
}

} // end of namespace botlib
} // end of namespace mcdane
