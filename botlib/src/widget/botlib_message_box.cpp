#include <commonlib_exception.h>
#include <commonlib_json_util.h>
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
                       float z,
                       float width,
                       float height,
                       const std::string& msg,
                       int buttons)
{
    init(x, y, z, width, height, msg, buttons);
}

void MessageBox::init(float x,
                      float y,
                      float z,
                      float width,
                      float height,
                      const std::string& msg,
                      int buttons)
{
}

void MessageBox::setVisible(bool v)
{
}

void MessageBox::present()
{
}

int MessageBox::processInput(const InputEvent& e)
{
    return 0;
}

void MessageBox::initBack(int& idx,
                          float x,
                          float y,
                          float z,
                          float width,
                          float height)
{
    Label* back = new Label(x, y, z, width, height);
    widgets_.setWidget(idx, back);
    ++idx;
}

void MessageBox::initMessage(int& idx,
                             float x,
                             float y,
                             float z,
                             float width,
                             float height,
                             const std::string& msg)
{
    float msgY = y + height/2.0f - k_messageMarginY - k_messageHeight/2.0f;
    float msgWidth = width - 2.0f * k_messageMarginX;
    float msgZ = z - 0.2f;
    Label* box = new Label(x, msgY, msgZ, msgWidth, k_messageHeight, msg);
    widgets_.setWidget(idx, box);
    ++idx;
}

void MessageBox::initButtons(int& idx,
                             float x,
                             float y,
                             float z,
                             float width,
                             float height,
                             int buttons)
{
    int buttonCount = getButtonCount(buttons);
    if (buttonCount == 0)
    {
        return;
    }

    float buttonY = y - height/2.0f + k_buttonMarginY + k_buttonHeight/2.0f;

    float buttonMarginX = width - buttonCount * k_buttonWidth -
                          (buttonCount - 1) * k_buttonSpacing;
    float buttonX = x - width/2.0f + buttonMarginX + k_buttonWidth / 2.0f;
    float buttonZ = z - 0.4f;

    if (buttons & BUTTON_OK)
    {
        Button* ok = new Button(buttonX, buttonY, buttonZ, 
    }
}

int MessageBox::getButtonCount(int buttons)
{
    int count = 0;
    if (bottons & BUTTON_OK)
    {
        ++count;
    }

    if (buttons & BUTTON_CANCEL)
    {
        ++count;
    }

    return count;
}

} // end of namespace botlib
} // end of namespace mcdane

