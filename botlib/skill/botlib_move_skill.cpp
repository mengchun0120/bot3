#include <commonlib_log.h>
#include <botlib_game_map.h>
#include <botlib_update_context.h>
#include <botlib_passthrough_collide_checker.h>
#include <botlib_robot.h>
#include <botlib_move_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MoveSkill::MoveSkill()
    : Skill()
    , destSet_(false)
{
}

MoveSkill::MoveSkill(const MoveSkillTemplate* t,
                     Robot* robot)
{
    init(t, robot);
}

void MoveSkill::init(const MoveSkillTemplate* t,
                     Robot* robot)
{
    Skill::init(t, robot, false);
    destSet_ = false;
}

void MoveSkill::update(UpdateContext& cxt)
{
    if (!enabled())
    {
        return;
    }

    if (!getTemplate()->hasDest())
    {
        updateWithoutDest(cxt);
    }
    else if (destSet_)
    {
        updateWithDest(cxt);
    }
}

void MoveSkill::setDest(const commonlib::Vector2& dest)
{
    Vector2 d = dest - robot_->pos();
    if (fuzzyEqualZero(d))
    {
        return;
    }

    float dist = d.norm();
    timeToDest_ = dist / robot_->speedNorm();
    robot_->setDirection(d / dist);
    destSet_ = true;
}

void MoveSkill::updateWithoutDest(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    Vector2 delta = robot_->speed() * cxt.timeDelta();

    bool collide = map.checkCollision(delta, robot_);
    if (collide)
    {
        setEnabled(false);
    }

    robot_->shiftPos(delta);
    map.repositionObj(robot_);

    checkPassthroughCollide(cxt);
}

void MoveSkill::updateWithDest(UpdateContext& cxt)
{
    bool reachDest = false;
    float timeDelta = cxt.timeDelta();
    if (timeDelta >= timeToDest_)
    {
        timeDelta = timeToDest_;
        reachDest = true;
    }

    GameMap& map = *(cxt.map());
    Vector2 delta = robot_->speed() * timeDelta;
    bool collide = map.checkCollision(delta, robot_);
    robot_->shiftPos(delta);
    map.repositionObj(robot_);

    if (reachDest || collide)
    {
        timeToDest_ = 0.0f;
        setEnabled(false);
        destSet_ = false;
    }
    else
    {
        timeToDest_ -= cxt.timeDelta();
    }

    checkPassthroughCollide(cxt);
}

void MoveSkill::checkPassthroughCollide(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    PassthroughCollideChecker checker(cxt, robot_);
    Region<int> r = map.getCollideArea(robot_->collideRegion());
    map.traverse(r, checker, {0, 2});
}

} // end of namespace botlib
} // end of namespace mcdane
