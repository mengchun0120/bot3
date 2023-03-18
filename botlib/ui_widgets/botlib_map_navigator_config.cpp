#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_map_navigator_config.h>
#include <commonlib_json_param.h>
#include <botlib_app_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MapNavigatorConfig::MapNavigatorConfig()
    : radius_(0.0f)
{
}

void MapNavigatorConfig::init(const std::string &fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string textureFile;
    std::vector<JsonParamPtr> params{
        jsonParam(textureFile, "texture", true, k_nonEmptyStrV),
        jsonParam(activateColor_, "activateColor", true),
        jsonParam(radius_, "radius", true, gt(0.0f)),
        jsonParam(controls_, "vertexArray", true),
    };

    parse(params, doc);
    initTexture(textureFile);

    LOG_INFO << "MapNavigatorConfig initialized" << LOG_END;
}

void MapNavigatorConfig::initTexture(const std::string &textureFile)
{
    const AppConfig &cfg = AppConfig::instance();
    std::string path = constructPath({cfg.picDir(), textureFile});
    texture_.init(path);
}

} // end of namespace botlib
} // end of namespace mcdane
