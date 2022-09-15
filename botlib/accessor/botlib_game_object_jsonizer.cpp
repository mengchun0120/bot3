#include <commonlib_json_utils.h>
#include <botlib_robot.h>
#include <botlib_game_object_jsonizer.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectJsonizer::GameObjectJsonizer(
                        rapidjson::Value& objects,
                        rapidjson::Document::AllocatorType& allocator)
    : objects_(objects)
    , allocator_(allocator)
{
}

bool GameObjectJsonizer::run(GameObject* obj)
{
    using namespace rapidjson;

    if (obj->type() != GameObjectType::ROBOT)
    {
        return true;
    }

    Robot* robot = static_cast<Robot*>(obj);
    Value robotJson(kObjectType);
    const char* type = (robot->side() == Side::AI) ? "robot" : "player";
    const char* templateName = robot->getTemplate()->name().c_str();

    robotJson.AddMember("type", jsonVal(type, allocator_), allocator_);
    robotJson.AddMember("template", jsonVal(templateName, allocator_), allocator_);
    robotJson.AddMember("pos", robot->pos().toJson(allocator_), allocator_);
    robotJson.AddMember("direction", robot->direction().toJson(allocator_), allocator_);

    objects_.PushBack(robotJson, allocator_);
}

} // end of namespace botlib
} // end of namespace mcdane

