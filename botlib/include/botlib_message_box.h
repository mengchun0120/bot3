#ifndef INCLUDED_BOTLIB_MESSAGE_BOX_H
#define INCLUDED_BOTLIB_MESSAGE_BOX_H

#include <string>
#include <botlib_widget_group.h>

namespace mcdane {
namespace botlib {

class MessageBox {
public:
    enum ButtonState {
        BUTTON_NONE = 0,
        BUTTON_OK = 1,
        BUTTON_CANCEL = 2
    };

    static void initConfig(const std::string& configFile);

    MessageBox() = default;

    MessageBox(float x,
               float y,
               float width,
               float height,
               const std::string& msg,
               int buttons);

    ~MessageBox() = default;

    void init(float x,
              float y,
              float width,
              float height,
              const std::string& msg,
              int buttons);

    void setVisible(bool v);

    void present();

    void process(const commonlib::InputEvent& e);

    inline bool visible() const;

    inline ButtonState buttonClicked() const;

private:
    void initBack(int idx,
                  float x,
                  float y,
                  float width,
                  float height);

    void initMessage(int idx,
                     float x,
                     float y,
                     float width,
                     float height,
                     const std::string& msg);

    void initButtons(int idx,
                     float x,
                     float y,
                     float width,
                     float height,
                     int buttonCount,
                     int buttons);

    int getButtonCount(int buttons);

    void onOKClicked();

    void onCancelClicked();

private:
    static float k_messageMarginX;
    static float k_messageMarginY;
    static float k_messageHeight;
    static float k_buttonMarginY;
    static float k_buttonSpacing;
    static float k_buttonWidth;
    static float k_buttonHeight;

    WidgetGroup widgets_;
    bool visible_;
    ButtonState buttonClicked_;
};

bool MessageBox::visible() const
{
    return visible_;
}

MessageBox::ButtonState MessageBox::buttonClicked() const
{
    return buttonClicked_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

