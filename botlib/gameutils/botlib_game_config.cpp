#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_game_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameConfig::GameConfig()
    : showHPIndicator_(false)
{
}

void GameConfig::init(const std::string& cfgFile)
{
    rapidjson::Document doc;
    readJson(doc, cfgFile);

    std::vector<JsonParamPtr> params{
        jsonParam(showHPIndicator_, "showHPIndicator")
    };

    parse(params, doc);
}

} // end of namespace botlib
} // end of namespace mcdane
