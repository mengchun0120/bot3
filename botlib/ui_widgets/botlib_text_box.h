#ifndef INCLUDED_BOTLIB_TEXT_BOX_H
#define INCLUDED_BOTLIB_TEXT_BOX_H

#include <string>
#include <vector>
#include <botlib_text_size.h>
#include <botlib_rectangle.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class TextBox {
public:
    static constexpr int k_defaultMaxTexLen = 1000;

    TextBox() = default;

    void init(float x,
              float y,
              float width,
              float height,
              TextSize textSize1=TextSize::MEDIUM,
              int maxTextLen=k_defaultMaxTexLen);

    void setPos(float x, float y) override;

    void shiftPos(float dx, float dy) override;

    void present() const override;

#ifdef DESKTOP_APP
    void onKey(const commonlib::KeyEvent &e) override;
#endif

    void onLostFocus() override;

    void onPointerDown(float x, float y) override;

    bool containPos(float x, float y) const override;

    inline std::string text() const;

    void setText(const std::string &s);

private:
    std::vector<char> text_;
    int textLen_;
    TextSize textSize_;
    Rectangle box_;
    Rectangle caret_;
    int firstIndex_;
    int caretIndex_;
    commonlib::Vector2 caretPos_;
};

std::string TextBox::text() const
{
    return std::string(text_.data(), textLen_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
