#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AppConfig::load(const std::string& fileName,
                     const std::string& appDir)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::vector<std::string> simpleVertexShaderFile, simpleFragShaderFile;

    std::vector<JsonParamPtr> params{
        jsonParam(width_, {"window", "width"}, true, gt(width_, 400)),
        jsonParam(height_, {"window", "height"}, true, gt(height_, 400)),
        jsonParam(title_, {"window", "title"}, true, nonempty(title_)),
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true,
                  gt(inputQueueCapacity_, 0)),
        jsonParam(simpleVertexShaderFile, {"shader", "simpleVertexShaderFile"},
                  true, nonempty(simpleVertexShaderFile)),
        jsonParam(simpleFragShaderFile, {"shader", "simpleFragShaderFile"},
                  true, nonempty(simpleFragShaderFile))
    };

    parse(params, doc);

    simpleVertexShaderFile_ = constructPath(appDir, simpleVertexShaderFile);
    simpleFragShaderFile_ = constructPath(appDir, simpleFragShaderFile);
}

} // end of namespace botlib
} // end of namespace mcdane

