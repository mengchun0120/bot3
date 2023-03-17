#include <commonlib_log.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_goodie_template.h>
#include <botlib_player.h>
#include <botlib_goodie_action.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void activateHealthFiller(const GoodieTemplate *t, Player &player)
{
    float hpDelta = player.getTemplate()->hp() * t->factor();
    player.addHP(hpDelta);
}

void activateDamageAmplifier(const GoodieTemplate *t, Player &player)
{
    player.setDamageFactor(t->factor());
}

void activateAttackAccelerator(const GoodieTemplate *t, Player &player)
{
    ShootMissileSkill *s = static_cast<ShootMissileSkill*>(
                                player.searchSkill(SkillType::SHOOT_MISSILE));
    s->setCoolDownFactor(t->factor());
}

void activateSpeedAccelerator(const GoodieTemplate *t, Player &player)
{
    float speedNorm = player.getTemplate()->speed() * t->factor();
    player.setSpeedNorm(speedNorm);
    player.resetSpeed();
}

void activateGodMode(const GoodieTemplate *t, Player &player)
{
    player.setInvincible(true);
}

void deactivateDamageAmplifier(Player &player)
{
    player.setDamageFactor(1.0f);
}

void deactivateAttackAccelerator(Player &player)
{
    ShootMissileSkill *s = static_cast<ShootMissileSkill*>(
                                player.searchSkill(SkillType::SHOOT_MISSILE));
    s->setCoolDownFactor(1.0f);
}

void deactivateSpeedAccelerator(Player &player)
{
    player.setSpeedNorm(player.getTemplate()->speed());
    player.resetSpeed();
}

void deactivateGodMode(Player &player)
{
    player.setInvincible(false);
}

void activateGoodie(const GoodieTemplate *t, Player &player)
{
    typedef void (*ActivateFunc)(const GoodieTemplate*, Player&);
    static std::vector<ActivateFunc> activateFuncs{
        activateHealthFiller,
        activateDamageAmplifier,
        activateAttackAccelerator,
        activateSpeedAccelerator,
        activateGodMode,
    };

    activateFuncs[static_cast<int>(t->goodieType())](t, player);
}

void deactivateGoodie(GoodieType type, Player &player)
{
    typedef void (*DeactivateFunc)(Player&);
    static std::vector<DeactivateFunc> deactivateFuncs{
        deactivateDamageAmplifier,
        deactivateAttackAccelerator,
        deactivateSpeedAccelerator,
        deactivateGodMode,
    };

    deactivateFuncs[lastingGoodieTypeIndex(type)](player);
}

} // end of namespace botlib
} // end of namespace mcdane
