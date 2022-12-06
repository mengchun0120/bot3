#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_showmap_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ShowMapScreenConfig::init(const std::string& cfgFile)
{
    rapidjson::Document doc;
    readJson(doc, cfgFile);

    std::vector<JsonParamPtr> params{
        jsonParam(mapFile_, "mapFile", true, k_nonEmptyStrV),
        jsonParam(deltaPerStroke_, "deltaPerStroke", true, gt(0.0f))
    };

    parse(params, doc);
}

void ShowMapScreenConfig::setMapFile(const std::string& fileName)
{
    mapFile_ = fileName;
}

} // end of namespace botlib
} // end of namespace mcdane

