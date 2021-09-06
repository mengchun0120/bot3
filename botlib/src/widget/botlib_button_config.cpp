#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_button_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ButtonConfig::load(const std::string& configFile,
                        const std::string& appDir)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::string textureFile;
    std::vector<JsonParam> params{
        jsonParam(normalTextColor_, {"normalTextColor"}, true,
                  check(normalTextColor_)),
        jsonParam(hoverTextColor_, {"hoverTextColor"}, true,
                  check(hoverTextColor_)),
        jsonParam(pressTextColor_, {"pressTextColor"}, true,
                  check(pressTextColor_)),
        jsonParam(textureFile, {"texture"}, true, nonempty(textureFile))
    };

    parse(params, doc);

    std::string texturePath = constructPath({appDir, textureFile});
    texture_.init(texturePath);
}

} // end of namespace botlib
} // end of namespace mcdane

