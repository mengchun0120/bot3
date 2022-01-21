#ifndef INCLUDED_BOTLIB_PLAYER_H
#define INCLUDED_BOTLIB_PLAYER_H

#include <botlib_player_template.h>
#include <botlib_robot.h>

namespace mcdane {
namespace botlib {

class Player: public Robot {
public:
    Player() = default;

    ~Player() override = default;

    void init(const PlayerTemplate* t,
              const commonlib::Vector2 pos1,
              const commonlib::Vector2 direction1);

    inline const PlayerTemplate* getTemplate() const;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;
};

const PlayerTemplate* Player::getTemplate() const
{
    return static_cast<const PlayerTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

