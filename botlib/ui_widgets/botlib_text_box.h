#ifndef INCLUDED_BOTLIB_TEXT_BOX_H
#define INCLUDED_BOTLIB_TEXT_BOX_H

#include <string>
#include <vector>
#include <botlib_rectangle.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class TextBox: public Widget {
public:
    static constexpr int k_defaultMaxTexLen = 1000;

    TextBox() = default;

    void init(float x,
              float y,
              float width,
              float height,
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
    void initBox(float width, float height);

    void initText(int maxTextLen);

    void initCaret();

    inline const char *visibleTextBegin() const;

    inline const char *visibleTextEnd() const;

private:
    Rectangle box_;
    commonlib::Vector2 boxPos_;
    std::vector<char> text_;
    int textLen_;
    int visibleTextStartIndex_;
    int visibleTextLen_;
    commonlib::Vector2 textPos_;
    float blinkDuration_;
    int caretIndex_;
    bool caretVisible_;
    commonlib::Vector2 caretPos_;
};

std::string TextBox::text() const
{
    return std::string(text_.data(), textLen_);
}

const char *TextBox::visibleTextBegin() const
{
    return text_.data() + visibleTextStartIndex_;
}

const char *TextBox::visibleTextEnd() const
{
    return visibleTextBegin() + visibleTextLen_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
