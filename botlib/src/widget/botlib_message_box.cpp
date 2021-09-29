#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_button.h>
#include <botlib_label.h>
#include <botlib_message_box.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

float MessageBox::k_messageMarginX;
float MessageBox::k_messageMarginY;
float MessageBox::k_messageHeight;
float MessageBox::k_buttonMarginY;
float MessageBox::k_buttonSpacing;
float MessageBox::k_buttonWidth;
float MessageBox::k_buttonHeight;

void MessageBox::initConfig(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(k_messageMarginX, {"messageMarginX"}, true,
                  gt(k_messageMarginX, 0.0f)),
        jsonParam(k_messageMarginY, {"messageMarginY"}, true,
                  gt(k_messageMarginY, 0.0f)),
        jsonParam(k_messageHeight, {"messageHeight"}, true,
                  gt(k_messageHeight, 0.0f)),
        jsonParam(k_buttonMarginY, {"buttonMarginY"}, true,
                  gt(k_buttonMarginY, 0.0f)),
        jsonParam(k_buttonSpacing, {"buttonSpacing"}, true,
                  gt(k_buttonSpacing, 0.0f)),
        jsonParam(k_buttonWidth, {"buttonWidth"}, true,
                  gt(k_buttonWidth, 0.0f)),
        jsonParam(k_buttonHeight, {"buttonHeight"}, true,
                  gt(k_buttonHeight, 0.0f))
    };

    parse(params, doc);
}

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
    int buttonCount = getButtonCount(buttons);
    int widgetCount = 2 + buttonCount;

    widgets_.init(widgetCount);
    initBack(0, x, y, width, height);
    initMessage(1, x, y, width, height, msg);
    initButtons(2, x, y, width, height, buttonCount, buttons);
    visible_ = false;
    buttonClicked_ = BUTTON_NONE;
}

void MessageBox::setVisible(bool v)
{
    visible_ = true;
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

void MessageBox::initBack(int idx,
                          float x,
                          float y,
                          float width,
                          float height)
{
    Label* back = new Label(x, y, width, height);
    widgets_.setWidget(idx, back);
}

void MessageBox::initMessage(int idx,
                             float x,
                             float y,
                             float width,
                             float height,
                             const std::string& msg)
{
    float msgY = y + height/2.0f - k_messageMarginY - k_messageHeight/2.0f;
    float msgWidth = width - 2.0f * k_messageMarginX;
    Label* box = new Label(x, msgY, msgWidth, k_messageHeight, msg,
                           TextSize::SMALL, HAlign::MIDDLE, VAlign::MIDDLE,
                           Label::defaultTextColor(), nullptr, nullptr);
    widgets_.setWidget(idx, box);
}

void MessageBox::initButtons(int idx,
                             float x,
                             float y,
                             float width,
                             float height,
                             int buttonCount,
                             int buttons)
{
    if (buttonCount == 0)
    {
        return;
    }

    float buttonY = y - height/2.0f + k_buttonMarginY + k_buttonHeight/2.0f;
    float buttonMarginX = (width - buttonCount * k_buttonWidth -
                           (buttonCount - 1) * k_buttonSpacing) / 2.0f;
    float buttonX = x - width/2.0f + buttonMarginX + k_buttonWidth / 2.0f;

    if (buttons & BUTTON_OK)
    {
        Button* okButton = new Button(buttonX, buttonY, k_buttonWidth,
                                      k_buttonHeight, "OK", TextSize::SMALL);
        Button::ActionFunc okAct = std::bind(&MessageBox::onOKClicked, this);
        okButton->setActionFunc(okAct);
        widgets_.setWidget(idx, okButton);
        buttonX += k_buttonWidth + k_buttonSpacing;
        ++idx;
    }

    if (buttons & BUTTON_CANCEL)
    {
        Button* cancelButton = new Button(buttonX, buttonY,
                                          k_buttonWidth, k_buttonHeight,
                                          "Cancel", TextSize::SMALL);
        Button::ActionFunc cancelAct = std::bind(&MessageBox::onCancelClicked,
                                                 this);
        cancelButton->setActionFunc(cancelAct);
        widgets_.setWidget(idx, cancelButton);
    }
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

} // end of namespace botlib
} // end of namespace mcdane

