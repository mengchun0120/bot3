#include <commonlib_exception.h>
#include <botlib_robot_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RobotTemplateParser::RobotTemplateParser(
            const NamedMap<MissileTemplate>& missileTemplateLib,
            const NamedMap<ComponentTemplate>& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(hp_, "hp", true, ge(0.0f)),
        jsonParam(armor_, "armor", true, ge(0.0f)),
        jsonParam(energy_, "energy", true, ge(0.0f)),
        jsonParam(speed_, "speed", true, ge(0.0f)),
        jsonParam(rechargeRate_, "rechargeRate", true, ge(0.0f)),
        jsonParam(missileName_, "missile", true, k_nonEmptyStrV),
        jsonParam(fireIntervalMS_, "fireIntervalMS", true, gt(0.0f)),
        jsonParam(firePoints_, "firePoints", true,
                  nonempty<std::vector<commonlib::Vector2>>()),
        jsonParam(fireDirections_, "fireDirections", true,
                  nonempty<std::vector<commonlib::Vector2>>())
      }
    , missileTemplateLib_(missileTemplateLib)
{
}

void RobotTemplateParser::load(const rapidjson::Value& v)
{
    CompositeObjectTemplateParser::load(v);
    parse(params_, v);

    missileTemplate_ = missileTemplateLib_.search(missileName_);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(ParseException,
                     "Cannot find MissileTemplate " + missileName_);
    }

    if (firePoints_.size() != fireDirections_.size())
    {
        THROW_EXCEPT(ParseException,
                     "firePoints size doens't match fireDirections size");
    }
}

} // end of namespace botlib
} // end of namespace mcdane

