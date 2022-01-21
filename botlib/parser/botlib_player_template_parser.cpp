#include <utility>
#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <botlib_player_template.h>
#include <botlib_player_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

PlayerTemplateParser::PlayerTemplateParser(
                            const MissileTemplateLib& missileTemplateLib,
                            const ComponentTemplateLib& componentTemplateLib)
    : RobotTemplateParser(missileTemplateLib, componentTemplateLib)
{
}

void PlayerTemplateParser::load(PlayerTemplate& t,
                                const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    RobotTemplateParser::load(doc);

    t.init(hp_,
           armor_,
           speed_,
           energy_,
           rechargeRate_,
           collideBreath_,
           missileTemplate_,
           fireIntervalMS_,
           std::forward<std::vector<Component>>(components_),
           std::forward<std::vector<Vector2>>(firePoints_),
           std::forward<std::vector<Vector2>>(fireDirections_));
}

} // end of namespace botlib
} // end of namespace mcdane

