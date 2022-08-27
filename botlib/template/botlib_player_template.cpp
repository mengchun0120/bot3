#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <botlib_player_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void PlayerTemplate::init(const std::string& playerTemplateFile,
                          const MissileTemplateLib& missileTemplateLib,
                          const ComponentTemplateLib& componentTemplateLib)
{
    rapidjson::Document doc;
    readJson(doc, playerTemplateFile);

    RobotTemplate::init("player", doc, missileTemplateLib, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

