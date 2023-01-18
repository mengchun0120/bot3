#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <commonlib_string_utils.h>
#include <botlib_context.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_passthrough_collide_checker.h>
#include <botlib_missile.h>
#include <botlib_skill_factory.h>
#include <botlib_robot.h>
#include <botlib_goodie.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Robot::Robot()
    : hp_(0.0f)
    , energy_(0.0f)
{
}

Robot::~Robot()
{
    if (!monitors_.empty())
    {
        notifyAndClearMonitors();
    }
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const Vector2& pos1,
                 const Vector2& direction1,
                 GameObjItemDeleter itemDeleter)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    hp_ = t->hp();
    speedNorm_ = t->speed();
    energy_ = t->energy();
    armor_ = t->armor();
    fireIntervalMS_ = t->fireIntervalMS();
    damageFactor_ = 1.0f;
    resetSpeed();
    hpIndicator_.reset(pos(), hpRatio());
    timeSinceLastShoot_ = 0.0f;
    dyingTime_ = 0.0f;
    resetArmorReduceRatio();
    if (itemDeleter)
    {
        monitors_.setDeleter(itemDeleter);
    }
    initSkills();
}

void Robot::present() const
{
    CompositeObject::present();
    if (Context::gameConfig().showHPIndicator())
    {
        hpIndicator_.present();
    }
}

void Robot::update(UpdateContext& cxt)
{
    if (state_ == GameObjectState::ALIVE)
    {
        updateAlive(cxt);
    }
    else if (state_ == GameObjectState::DYING)
    {
        updateDying(cxt);
    }

    GameObject::update(cxt);
}

void Robot::shiftPos(const Vector2& delta)
{
    CompositeObject::shiftPos(delta);
    hpIndicator_.shiftPos(delta);
}

void Robot::setDirection(const Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetSpeed();
}

void Robot::addHP(float delta)
{
    if (state_ != GameObjectState::ALIVE || delta <= 0.0f)
    {
        return;
    }

    hp_ = std::min(hp_ + delta, getTemplate()->hp());
    hpIndicator_.reset(pos(), hpRatio());
}

void Robot::addEnergy(float delta)
{
    energy_ = clamp(energy_+delta, 0.0f, getTemplate()->energy());
}

void Robot::doDamage(float damage, UpdateContext& cxt)
{
    if (state_ != GameObjectState::ALIVE || damage <= 0.0f || invincible())
    {
        return;
    }

    if (armor_ > 0.0f)
    {
        armor_ = std::max(armor_ - armorReduceRatio_ * damage, 0.0f);
        resetArmorReduceRatio();
    }
    else
    {
        hp_ = std::max(hp_ - damage, 0.0f);
        if (hp_ <= 0.0f)
        {
            setState(GameObjectState::DYING);
            notifyAndClearMonitors();
        }

        hpIndicator_.reset(pos(), hpRatio());
    }
}

bool Robot::canBeDumped(GameMap& map) const
{
    return state_ == GameObjectState::DYING && !map.canSee(this);
}

void Robot::setSpeedNorm(float speedNorm1)
{
    if (speedNorm1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid speedNorm");
    }

    speedNorm_ = speedNorm1;
}

void Robot::setFireIntervalMS(float fireIntervalMS1)
{
    if (fireIntervalMS1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid fireIntervalMS");
    }

    fireIntervalMS_ = fireIntervalMS1;
}

void Robot::setArmor(float armor1)
{
    if (armor1 < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid armor");
    }

    armor_ = armor1;
}

void Robot::setDamageFactor(float factor)
{
    if (factor < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid factor");
    }

    damageFactor_ = factor;
}

void Robot::resetSpeed()
{
    speed_ = speedNorm_ * direction_;
}

void Robot::addMonitor(GameObject* obj,
                       GameObjItemPool& pool)
{
    GameObjectItem* item = pool.alloc(obj);
    monitors_.pushBack(item);
}

void Robot::removeMonitor(GameObject* obj)
{
    GameObjectItem* i = monitors_.first();

    for (; i; i = i->next())
    {
        if (i->item() == obj)
        {
            break;
        }
    }

    if (i)
    {
        monitors_.remove(i);
    }
}

Skill* Robot::searchSkill(SkillType skillType)
{
    for (auto it = skills_.begin(); it != skills_.end(); ++it)
    {
        Skill* skill = it->get();
        if (skill->getTemplate()->type() == skillType)
        {
            return skill;
        }
    }

    return nullptr;
}

bool Robot::setSkillEnabled(SkillType skillType, bool enabled)
{
    Skill* skill = searchSkill(skillType);
    if (skill)
    {
        skill->setEnabled(enabled);
        return true;
    }

    return false;
}

void Robot::shoot(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    const MissileTemplate* t = getTemplate()->missileTemplate();

    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
        if (it->getTemplate()->type() != ComponentType::GUN)
        {
            continue;
        }

        Missile* missile = new Missile();
        missile->init(t, side_, it->firePos(), it->direction(), damageFactor_);

        map.addObj(missile);
    }
}

void Robot::initSkills()
{
    auto& skillTemplates = getTemplate()->skills();

    skills_.resize(skillTemplates.size());
    for (std::size_t i = 0; i < skills_.size(); ++i)
    {
        Skill* s = SkillFactory::create(skillTemplates[i], this);
        skills_[i].reset(s);
    }
}

void Robot::updateAlive(UpdateContext& cxt)
{
    updateEnergy(cxt.timeDelta());
    updateSkills(cxt);
}

void Robot::updateDying(UpdateContext& cxt)
{
    dyingTime_ += cxt.timeDelta();
    if (dyingTime_ >= getTemplate()->dyingDuration())
    {
        cxt.dumper().add(this);
    }
    else
    {
        setAlpha(1.0f - dyingTime_ / getTemplate()->dyingDuration());
    }
}

void Robot::updateSkills(UpdateContext& cxt)
{
    for (std::size_t i = 0; i < skills_.size(); ++i)
    {
        Skill* s = skills_[i].get();
        if (state_ == GameObjectState::ALIVE)
        {
            s->update(cxt);
        }
    }
}

void Robot::resetArmorReduceRatio()
{
    constexpr float MIN_RATIO = 0.1f;
    constexpr float MAX_RATIO = 1.0f;
    constexpr float SLOPE = (MIN_RATIO - MAX_RATIO) / 1000.0f;

    armorReduceRatio_ = clamp(MAX_RATIO + SLOPE * armor_, MIN_RATIO, MAX_RATIO);
}

void Robot::updateEnergy(float timeDelta)
{
    energy_ = std::min(energy_ + timeDelta * getTemplate()->rechargeRate(),
                       getTemplate()->energy());
}

void Robot::notifyAndClearMonitors()
{
    for (GameObjectItem* i = monitors_.first(); i; i = i->next())
    {
        i->item()->notify(this);
    }

    monitors_.clear();
}

} // end of namespace botlib
} // end of namespace mcdane

