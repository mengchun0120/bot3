#ifndef INCLUDED_BOTLIB_BUTTON_H
#define INCLUDED_BOTLIB_BUTTON_H

#include <functional>
#include <string>
#include <botlib_constants.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class Button: public Widget {
public:
    using ActionFunc = std::function<void()>;

public:
    static void initConfig(const std::string& configFile,
                           const std::string& appDir);

    Button();

    virtual ~Button()
    {}

    void init(float x,
              float y,
              float z,
              float width,
              float height,
              const std::string& text,
              TextSize textSize=TEXT_SIZE_MEDIUM,
              bool visible=true,
              bool acceptInput=true);

    void present() const override;

    void setText(const std::string &text);

    void setActionFunc(const ActionFunc &actionFunc);

    void setPos(float x,
                float y,
                float z) override;

    void shiftPos(float dx,
                  float dy) override;

#ifdef DESKTOP_APP
    void process(const KeyEvent &event) override;

    void process(const MouseMoveEvent &event) override;

    void process(const MouseButtonEvent &event) override;

void onMouseOut() override;
#endif

private:
    static void validateTextColor();

    void resetTextPos();

private:
    enum State {
        STATE_NORMAL,
        STATE_HOVER,
        STATE_PRESSED,
        STATE_COUNT
    };

    static std::vector<commonlib::Color> k_textColors;
    static commonlib::Texture k_texture;

    std::string text_;
    commonlib::Vecotr2 textPos_;
    State state_;
    TextSize textSize_;
    ActionFunc action_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

