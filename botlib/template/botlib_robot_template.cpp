#include <utility>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void RobotTemplate::init(const rapidjson::Value& v,
                         const MissileTemplateLib& missileTemplateLib,
                         const ComponentTemplateLib& componentTemplateLib)
{
    std::string missileName;
    std::vector<JsonParamPtr> params{
        jsonParam(hp_, "hp", true, ge(0.0f)),
        jsonParam(armor_, "armor", true, ge(0.0f)),
        jsonParam(energy_, "energy", true, ge(0.0f)),
        jsonParam(speed_, "speed", true, ge(0.0f)),
        jsonParam(rechargeRate_, "rechargeRate", true, ge(0.0f)),
        jsonParam(missileName, "missile", true, k_nonEmptyStrV),
        jsonParam(fireIntervalMS_, "fireIntervalMS", true, gt(0.0f)),
        jsonParam(firePoints_, "firePoints", true,
                  nonempty<std::vector<commonlib::Vector2>>()),
        jsonParam(fireDirections_, "fireDirections", true,
                  nonempty<std::vector<commonlib::Vector2>>()),
        jsonParam(dyingDuration_, "dyingDuration", true, gt(0.0f))
    };

    parse(params, v);

    missileTemplate_ = missileTemplateLib.search(missileName);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find MissileTemplate " + missileName);
    }

    CompositeObjectTemplate::init(GameObjectType::ROBOT, v, componentTemplateLib);
}

rapidjson::Value RobotTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "RobotTemplate", allocator);
    v.AddMember("hp", hp_, allocator);
    v.AddMember("armor", armor_, allocator);
    v.AddMember("speed", speed_, allocator);
    v.AddMember("energy", energy_, allocator);
    v.AddMember("rechargeRate", rechargeRate_, allocator);
    v.AddMember("fireIntervalMS", fireIntervalMS_, allocator);
    v.AddMember("firePoints", jsonVal(firePoints_, allocator), allocator);
    v.AddMember("fireDirections", jsonVal(fireDirections_, allocator), allocator);
    v.AddMember("missileTemplate", missileTemplate_->id(), allocator);
    v.AddMember("base", CompositeObjectTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

