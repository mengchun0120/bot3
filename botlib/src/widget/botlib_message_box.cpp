#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_button.h>
#include <botlib_label.h>
#include <botlib_message_box.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

float MessageBox::k_messageMarginX;
float MessageBox::k_messageMarginY;
float MessageBox::k_buttonMarginY;
float MessageBox::k_buttonSpacing;
float MessageBox::k_buttonWidth;
float MessageBox::k_buttonHeight;

void MessageBox::initConfig(const rapidjson::Value& cfg)
{
    if (!cfg.IsObject())
    {
        THROW_EXCEPT(InvalidArgumentException, "Cfg must be an object");
    }

    std::vector<JsonParamPtr> params{
        jsonParam(k_messageMarginX, {"messageMarginX"}, true,
                  gt(k_messageMarginX, 0.0f)),
        jsonParam(k_messageMarginY, {"messageMarginY"}, true,
                  gt(k_messageMarginY, 0.0f)),
        jsonParam(k_buttonMarginY, {"buttonMarginY"}, true,
                  gt(k_buttonMarginY, 0.0f)),
        jsonParam(k_buttonSpacing, {"buttonSpacing"}, true,
                  gt(k_buttonSpacing, 0.0f)),
        jsonParam(k_buttonWidth, {"buttonWidth"}, true,
                  gt(k_buttonWidth, 0.0f)),
        jsonParam(k_buttonHeight, {"buttonHeight"}, true,
                  gt(k_buttonHeight, 0.0f))
    };

    parse(params, cfg);
}

MessageBox::MessageBox(float x,
               float y,
               float z,
               float width,
               float height,
               const std::string& msg,
               int buttons)
{
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

} // end of namespace botlib
} // end of namespace mcdane

