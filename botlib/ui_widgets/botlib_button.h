#ifndef INCLUDED_BOTLIB_BUTTON_H
#define INCLUDED_BOTLIB_BUTTON_H

#include <functional>
#include <string>
#include <commonlib_color.h>
#include <commonlib_texture.h>
#include <botlib_text_size.h>
#include <botlib_constants.h>
#include <botlib_rectangular_widget.h>

namespace mcdane {
namespace botlib {

class Button: public RectangularWidget {
public:
    using ActionFunc = std::function<void()>;

    enum State {
        STATE_NORMAL,
        STATE_HOVER,
        STATE_PRESSED,
        STATE_COUNT
    };

public:
    Button();

    Button(float x,
           float y,
           float width,
           float height,
           const std::string &text,
           TextSize textSize=TextSize::MEDIUM,
           bool visible=true,
           bool acceptInput=true);

    ~Button() override = default;

    void init(float x,
              float y,
              float width,
              float height,
              const std::string &text,
              TextSize textSize=TextSize::MEDIUM,
              bool visible=true,
              bool acceptInput=true);

    void present() const override;

    void setText(const std::string &text);

    void setActionFunc(const ActionFunc &actionFunc);

    void setPos(float x, float y) override;

    void shiftPos(float dx, float dy) override;

#ifdef DESKTOP_APP
    void onKey(const commonlib::KeyEvent &e);
#endif

    void onPointerOut() override;

    void onPointerOver() override;

    void onPointerDown() override;

private:
    void resetTextPos();

private:
    std::string text_;
    commonlib::Vector2 textPos_;
    State state_;
    TextSize textSize_;
    ActionFunc action_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

