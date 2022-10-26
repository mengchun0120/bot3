#ifndef INCLUDED_BOTLIB_GAME_OBJECT_JSONIZER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_JSONIZER_H

#include <rapidjson/document.h>
#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectJsonizer: public GameMapAccessor {
public:
    GameObjectJsonizer(rapidjson::Value& objects,
                       rapidjson::Document::AllocatorType& allocator);

    bool run(GameObject* obj) override;

private:
    rapidjson::Value robotJson(GameObject* obj);

    rapidjson::Value tileJson(GameObject* obj);

private:
    rapidjson::Value& objects_;
    rapidjson::Document::AllocatorType& allocator_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
