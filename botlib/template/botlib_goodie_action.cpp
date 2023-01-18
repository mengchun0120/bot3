#include <commonlib_log.h>
#include <botlib_goodie.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_player.h>
#include <botlib_goodie_action.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void activateHealthFiller(const GoodieTemplate* t,
                          Player& player)
{
    float hpDelta = player.getTemplate()->hp() * t->factor();
    player.addHP(hpDelta);
}

void activateAttackAccelerator(const GoodieTemplate* t,
                               Player& player)
{
    ShootMissileSkill* s = static_cast<ShootMissileSkill*>(
                                player.searchSkill(SkillType::SHOOT_MISSILE));
    s->setCoolDownFactor(t->factor());
}

void deactivateAttackAccelerator(Player& player)
{
    ShootMissileSkill* s = static_cast<ShootMissileSkill*>(
                                player.searchSkill(SkillType::SHOOT_MISSILE));
    s->setCoolDownFactor(1.0f);
}

void activateSpeedAccelerator(const GoodieTemplate* t,
                              Player& player)
{
    float speedNorm = player.getTemplate()->speed() * t->factor();
    player.setSpeedNorm(speedNorm);
    player.resetSpeed();
}

void deactivateSpeedAccelerator(Player& player)
{
    player.setSpeedNorm(player.getTemplate()->speed());
    player.resetSpeed();
}

void activateDamageAmplifier(const GoodieTemplate* t,
                             Player& player)
{
    player.setDamageFactor(t->factor());
}

void deactivateDamageAmplifier(Player& player)
{
    player.setDamageFactor(1.0f);
}

void activateGodMode(const GoodieTemplate* t,
                     Player& player)
{
    player.setFlag(GameObject::FLAG_INVINCIBLE, true);
}

void deactivateGodMode(Player& player)
{
    player.setFlag(GameObject::FLAG_INVINCIBLE, false);
}

} // end of namespace botlib
} // end of namespace mcdane
