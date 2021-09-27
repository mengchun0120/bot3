#ifndef INCLUDED_BOTLIB_MESSAGE_BOX_H
#define INCLUDED_BOTLIB_MESSAGE_BOX_H

#include <string>
#include <rapidjson/document.h>
#include <botlib_widget_group.h>

namespace mcdane {
namespace botlib {

class MessageBox {
public:
    enum {
        BUTTON_OK = 1,
        BUTTON_CANCEL = 2
    };

    static void initConfig(const rapidjson::Value& cfg);

    MessageBox() = default;

    MessageBox(float x,
               float y,
               float z,
               float width,
               float height,
               const std::string& msg,
               int buttons);

    ~MessageBox() = default;

    void init(float x,
              float y,
              float z,
              float width,
              float height,
              const std::string& msg,
              int buttons);

    void setVisible(bool v);

    void present();

    int processInput(const commonlib::InputEvent& e);

    inline bool visible() const;

private:
    static float k_messageMarginX;
    static float k_messageMarginY;
    static float k_buttonMarginY;
    static float k_buttonSpacing;
    static float k_buttonWidth;
    static float k_buttonHeight;

    WidgetGroup widgets_;
    bool visible_;
};

bool MessageBox::visible() const
{
    return visible_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

