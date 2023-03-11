#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <botlib_player_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void PlayerTemplate::init(const std::string& playerTemplateFile,
                          const MissileTemplateLib& missileTemplateLib,
                          const ComponentTemplateLib& componentTemplateLib,
                          const SkillTemplateLib& skillTemplateLib,
                          const commonlib::InputMap& inputMap)
{
    rapidjson::Document doc;
    readJson(doc, playerTemplateFile);

    RobotTemplate::init("player", doc, missileTemplateLib, componentTemplateLib,
                        skillTemplateLib);
    initInputSkillMap(doc, inputMap);
}

#ifdef DESKTOP_APP
void PlayerTemplate::initInputSkillMap(const rapidjson::Value& v,
                                       const commonlib::InputMap& inputMap)
{
    const rapidjson::Value* m = findJson(v, {"inputSkillMap"});
    if (!m->IsObject())
    {
        THROW_EXCEPT(InvalidArgumentException, "inputSkillMap is invalid!");
    }

    for (auto it = m->MemberBegin(); it != m->MemberEnd(); ++it)
    {
        std::string inputName(it->name.GetString());
        std::string skillName(it->value.GetString());

        int input = inputMap.get(inputName);
        if (input == -1)
        {
            THROW_EXCEPT(InvalidArgumentException, "Invalid input " + inputName);
        }

        auto mapIt = inputSkillMap_.find(input);
        if (mapIt != inputSkillMap_.end())
        {
            THROW_EXCEPT(InvalidArgumentException,
                         "Skill has already been set for " + inputName);
        }

        SkillType skill = toSkillType(skillName);
        inputSkillMap_[input] = skill;
    }
}
#elif __ANDROID__
void PlayerTemplate::initInputSkillMap(const rapidjson::Value& v,
                                       const commonlib::InputMap& inputMap)
{
}
#endif

} // end of namespace botlib
} // end of namespace mcdane

