#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <botlib_robot.h>
#include <botlib_tile.h>
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

    Value json;

    switch (obj->type())
    {
        case GameObjectType::ROBOT:
            json = robotJson(obj);
            break;
        case GameObjectType::TILE:
            json = tileJson(obj);
            break;
        default:
            return true;
    }

    objects_.PushBack(json, allocator_);

    return true;
}

rapidjson::Value GameObjectJsonizer::robotJson(GameObject* obj)
{
    using namespace rapidjson;

    rapidjson::Value json(kObjectType);

    Robot* robot = static_cast<Robot*>(obj);
    std::string type = (robot->side() == Side::AI) ? "robot" : "player";
    std::string templateName = robot->getTemplate()->name();

    json.AddMember("type", jsonVal(type, allocator_), allocator_);
    json.AddMember("template", jsonVal(templateName, allocator_), allocator_);
    json.AddMember("pos", robot->pos().toJson(allocator_), allocator_);
    json.AddMember("direction", robot->direction().toJson(allocator_), allocator_);

    return json;
}

rapidjson::Value GameObjectJsonizer::tileJson(GameObject* obj)
{
    using namespace rapidjson;

    rapidjson::Value json(kObjectType);
    Tile* tile = static_cast<Tile*>(obj);
    std::string templateName = tile->getTemplate()->name();

    json.AddMember("type", jsonVal("tile", allocator_), allocator_);
    json.AddMember("template", jsonVal(templateName, allocator_), allocator_);
    json.AddMember("pos", tile->pos().toJson(allocator_), allocator_);
    json.AddMember("direction", tile->direction().toJson(allocator_), allocator_);

    return json;
}

} // end of namespace botlib
} // end of namespace mcdane

