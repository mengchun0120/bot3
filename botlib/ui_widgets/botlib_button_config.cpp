#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_button_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ButtonConfig::init(const std::string& configFile,
                        const std::string& picDir)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::string textureFile;
    std::vector<JsonParamPtr> params{
        jsonParam(textColors_, {"textColor"}),
        jsonParam(textureFile, {"texture"}, true, k_nonEmptyStrV)
    };

    parse(params, doc);

    validateTextColor();

    textureFile = constructPath({picDir, textureFile});
    texture_.init(textureFile);

    LOG_INFO << "Button config finished successfully" << LOG_END;
}

void ButtonConfig::validateTextColor()
{
    if (textColors_.size() != Button::STATE_COUNT)
    {
        THROW_EXCEPT(MyException, "Size of textColor is invalid");
    }
}


} // end of namespace botlib
} // end of namespace mcdane

