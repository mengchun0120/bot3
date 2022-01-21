#include <utility>
#include <sstream>
#include <commonlib_exception.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate(float collideBreath,
                           float hp,
                           bool invincible,
                           std::vector<Component>&& components)
    : CompositeObjectTemplate(GameObjectType::TILE,
                              collideBreath,
                              invincible,
                              std::forward<std::vector<Component>>(components))
    , hp_(hp)
{
}

void TileTemplate::init(float collideBreath,
                        float hp,
                        bool invincible,
                        std::vector<Component>&& components)
{
    CompositeObjectTemplate::init(GameObjectType::TILE,
                                  collideBreath,
                                  invincible,
                                  std::forward<std::vector<Component>>(components));
    hp_ = hp;
}

rapidjson::Value TileTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "TileTemplate", allocator);
    v.AddMember("hp", hp_, allocator);
    v.AddMember("base", CompositeObjectTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

