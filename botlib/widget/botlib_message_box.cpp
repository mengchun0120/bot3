#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_message_box.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MessageBox::MessageBox(float x,
                       float y,
                       float width,
                       float height,
                       const std::string& msg,
                       int buttons)
{
    init(x, y, width, height, msg, buttons);
}

void MessageBox::init(float x,
                      float y,
                      float width,
                      float height,
                      const std::string& msg,
                      int buttons)
{
    pos_[0] = x;
    pos_[1] = y;
    size_[0] = width;
    size_[1] = height;
    widgets_.init(WIDGET_COUNT);
    initBack();
    initMessage(msg);
    initButtons(buttons);
    visible_ = false;
    buttonClicked_ = BUTTON_NONE;
}

void MessageBox::setVisible(bool v)
{
    visible_ = v;
}

void MessageBox::setText(const std::string& text)
{
    getMsg().setText(text);
}

void MessageBox::setButtons(int buttons)
{
    configButtons(buttons);
}

void MessageBox::present()
{
    if (visible_)
    {
        widgets_.present();
    }
}

void MessageBox::process(const InputEvent& e)
{
    buttonClicked_ = BUTTON_NONE;
    if (visible_)
    {
        widgets_.process(e);
    }
}

void MessageBox::initBack()
{
    Label* back = new Label(x(), y(), width(), height());
    widgets_.setWidget(IDX_BACK, back);
}

void MessageBox::initMessage(const std::string& msg)
{
    const MessageBoxConfig& cfg = Context::msgBoxConfig();

    float msgY = y() + height()/2.0f - cfg.messageMarginY() - cfg.messageHeight()/2.0f;
    float msgWidth = width() - 2.0f * cfg.messageMarginX();
    Label* box = new Label(x(), msgY, msgWidth, cfg.messageHeight(), msg,
                           TextSize::SMALL, HAlign::MIDDLE, VAlign::MIDDLE,
                           nullptr, nullptr, &cfg.messageBorderColor());
    widgets_.setWidget(IDX_MSG, box);
}

void MessageBox::initButtons(int buttons)
{
    const MessageBoxConfig& cfg = Context::msgBoxConfig();

    Button* okButton = new Button(0.0f, 0.0f, cfg.buttonWidth(), cfg.buttonHeight(),
                                  "OK", TextSize::SMALL, false);
    Button::ActionFunc okAct = std::bind(&MessageBox::onOKClicked, this);
    okButton->setActionFunc(okAct);
    widgets_.setWidget(IDX_OK, okButton);

    Button* cancelButton = new Button(0.0f, 0.0f, cfg.buttonWidth(), cfg.buttonHeight(),
                                      "Cancel", TextSize::SMALL, false);
    Button::ActionFunc cancelAct = std::bind(&MessageBox::onCancelClicked,
                                             this);
    cancelButton->setActionFunc(cancelAct);
    widgets_.setWidget(IDX_CANCEL, cancelButton);

    configButtons(buttons);
}

int MessageBox::getButtonCount(int buttons)
{
    int count = 0;
    if (buttons & BUTTON_OK)
    {
        ++count;
    }

    if (buttons & BUTTON_CANCEL)
    {
        ++count;
    }

    return count;
}

void MessageBox::onOKClicked()
{
    visible_ = false;
    buttonClicked_ = BUTTON_OK;
}

void MessageBox::onCancelClicked()
{
    visible_ = false;
    buttonClicked_ = BUTTON_CANCEL;
}

void MessageBox::configButtons(int buttons)
{
    const MessageBoxConfig& cfg = Context::msgBoxConfig();

    int buttonCount = getButtonCount(buttons);
    float buttonY = y() - height()/2.0f + cfg.buttonMarginY() + cfg.buttonHeight()/2.0f;
    float buttonMarginX = (width() - buttonCount * cfg.buttonWidth() -
                           (buttonCount - 1) * cfg.buttonSpacing()) / 2.0f;
    float buttonX = x() - width()/2.0f + buttonMarginX + cfg.buttonWidth() / 2.0f;

    if (buttons & BUTTON_OK)
    {
        showButton(IDX_OK, buttonX, buttonY);
        buttonX += cfg.buttonWidth() + cfg.buttonSpacing();
    }
    else
    {
        hideButton(IDX_OK);
    }

    if (buttons & BUTTON_CANCEL)
    {
        showButton(IDX_CANCEL, buttonX, buttonY);
    }
    else
    {
        hideButton(IDX_CANCEL);
    }
}

void MessageBox::showButton(unsigned int idx,
                            float x,
                            float y)
{
    Button& button = getButton(idx);
    button.setPos(x, y);
    button.setVisible(true);
}

void MessageBox::hideButton(unsigned int idx)
{
    Button& button = getButton(idx);
    button.setVisible(false);
}

} // end of namespace botlib
} // end of namespace mcdane

