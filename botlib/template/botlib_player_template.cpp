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

    RobotTemplate::init(doc, missileTemplateLib, componentTemplateLib);

    LOG_DEBUG << "PlayerTemplate loaded successfully " << *this << LOG_END;
}

rapidjson::Value PlayerTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "PlayerTemplate", allocator);
    v.AddMember("base", RobotTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

