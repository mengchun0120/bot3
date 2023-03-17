#ifndef INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H
#define INCLUDED_BOTLIB_PASSTHROUGH_COLLIDE_CHECKER_H

namespace mcdane {
namespace botlib {

class UpdateContext;
class GameObject;
class Robot;
class Missile;
class Goodie;

class PassthroughCollideChecker {
public:
    PassthroughCollideChecker(UpdateContext &cxt, Robot *robot);

    bool operator()(GameObject *obj);

private:
    void collideMissile(Missile *missile);

    void collideGoodie(Goodie *goodie);

private:
    UpdateContext &cxt_;
    Robot *robot_;
};


} // end of namespace botlib
} // end of namespace mcdane

#endif
