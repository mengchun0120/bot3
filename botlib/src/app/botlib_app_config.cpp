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

    std::vector<JsonParamPtr> params{
        jsonParam(width_, {"window", "width"}, true, gt(width_, 400)),
        jsonParam(height_, {"window", "height"}, true, gt(height_, 400)),
        jsonParam(title_, {"window", "title"}, true, nonempty(title_)),
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true,
                  gt(inputQueueCapacity_, 0)),
        jsonParam(simpleVertexShaderFile_, {"shader", "simpleVertexShaderFile"},
                  true, nonempty(simpleVertexShaderFile_)),
        jsonParam(simpleFragShaderFile_, {"shader", "simpleFragShaderFile"},
                  true, nonempty(simpleFragShaderFile_))
    };

    parse(params, doc);

    completeFilePath(appDir);
}

void AppConfig::completeFilePath(const std::string& appDir)
{
    simpleVertexShaderFile_ = constructPath({appDir, "res", "glsl",
                                            simpleVertexShaderFile_});
    simpleFragShaderFile_ = constructPath({appDir, "res", "glsl",
                                          simpleFragShaderFile_});
}

} // end of namespace botlib
} // end of namespace mcdane

