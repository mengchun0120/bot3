#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_text_system.h>
#include <botlib_text_box_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void TextBoxConfig::init(const std::string &fileName,
                         const TextSystem &textSys)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string textSizeStr;
    float caretWidth;
    std::vector<JsonParamPtr> params{
        jsonParam(blinkTime_, "blinkTime", true, gt(0.0f)),
        jsonParam(caretWidth, "caretWidth", true, gt(0.0f)),
        jsonParam(textSizeStr, "textSize"),
        jsonParam(borderColor_, "borderColor"),
        jsonParam(backColor_, "backColor"),
        jsonParam(textColor_, "textColor"),
        jsonParam(caretColor_, "caretColor"),
        jsonParam(leftMargin_, "leftMargin"),
        jsonParam(topMargin_, "topMargin"),
        jsonParam(bottomMargin_, "bottomMargin"),
        jsonParam(minWidth_, "minWidth", true, gt(0.0f)),
    };

    parse(params, doc);

    textSize_ = toTextSize(textSizeStr);
    textHeight_ = textSys.getHeight(textSize_);
    caretRect_.init(caretWidth, textHeight_);
    minHeight_ = textHeight_ + topMargin_ + bottomMargin_;

    LOG_INFO << "TextBoxConfig initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane
