#ifndef INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class UpdateContext;
class Robot;
class Missile;
class Goodie;

class PassthroughCollideChecker: public GameMapAccessor {
public:
    PassthroughCollideChecker(UpdateContext& cxt,
                              Robot* robot);

    bool run(GameObject* obj) override;

private:
    void collideMissile(Missile* missile);

    void collideGoodie(Goodie* goodie);

private:
    UpdateContext& cxt_;
    Robot* robot_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

