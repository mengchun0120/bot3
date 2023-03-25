#ifndef INCLUDED_BOTLIB_MESSAGE_BOX_H
#define INCLUDED_BOTLIB_MESSAGE_BOX_H

#include <string>
#include <botlib_button.h>
#include <botlib_label.h>
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

    MessageBox() = default;

    MessageBox(float x,
               float y,
               float width,
               float height,
               const std::string &msg,
               int buttons);

    ~MessageBox() = default;

    void init(float x,
              float y,
              float width,
              float height,
              const std::string &msg,
              int buttons);

    void setVisible(bool v);

    void setText(const std::string &text);

    void setButtons(int buttons);

    void present();

    void process(const commonlib::InputEvent &e);

    inline bool visible() const;

    inline ButtonState buttonClicked() const;

    inline float x() const;

    inline float y() const;

    inline float width() const;

    inline float height() const;

private:
    void initBack();

    void initMessage(const std::string &msg);

    void initButtons(int buttons);

    int getButtonCount(int buttons);

    void onOKClicked();

    void onCancelClicked();

    void configButtons(int buttons);

    void showButton(unsigned int idx,
                    float x,
                    float y);

    void hideButton(unsigned int idx);

    inline Button &getButton(unsigned int idx);

    inline Label &getMsg();

private:
    enum {
        IDX_BACK,
        IDX_MSG,
        IDX_OK,
        IDX_CANCEL,
        WIDGET_COUNT
    };

    commonlib::Vector2 pos_;
    commonlib::Vector2 size_;
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

float MessageBox::x() const
{
    return pos_[0];
}

float MessageBox::y() const
{
    return pos_[1];
}

float MessageBox::width() const
{
    return size_[0];
}

float MessageBox::height() const
{
    return size_[1];
}

Button &MessageBox::getButton(unsigned int idx)
{
    return *(widgets_.widget<Button>(idx));
}

Label &MessageBox::getMsg()
{
    return *(widgets_.widget<Label>(IDX_MSG));
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
