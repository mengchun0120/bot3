#include <botlib_goodie.h>
#include <botlib_player.h>
#include <botlib_goodie_action.h>

namespace mcdane {
namespace botlib {

void activateHealthFiller(Goodie& goodie, Player& player)
{
    float hpDelta = player.getTemplate()->hp() * goodie.getTemplate()->factor();
    player.addHP(hpDelta);
}

void activateAttackAccelerator(Goodie& goodie, Player& player)
{
    float intervalMS = player.getTemplate()->fireIntervalMS() *
                       goodie.getTemplate()->factor();
    player.setFireIntervalMS(intervalMS);
}

void deactivateAttackAccelerator(Goodie& goodie, Player& player)
{
    player.setFireIntervalMS(player.getTemplate()->fireIntervalMS());
}

void activateSpeedAccelerator(Goodie& goodie, Player& player)
{
    float speedNorm = player.getTemplate()->speed() *
                      goodie.getTemplate()->factor();
    player.setSpeedNorm(speedNorm);
}

void deactivateSpeedAccelerator(Goodie& goodie, Player& player)
{
    player.setSpeedNorm(player.getTemplate()->speed());
}

void activateDamageAmplifier(Goodie& goodie, Player& player)
{
    player.setDamageFactor(goodie.getTemplate()->factor());
}

void deactivateDamageAmplifier(Goodie& goodie, Player& player)
{
    player.setDamageFactor(1.0f);
}

void activateArmorEnhancer(Goodie& goodie, Player& player)
{
    float armor = player.getTemplate()->armor() * goodie.getTemplate()->factor();
    player.setArmor(armor);
}

void deactivateArmorEnhancer(Goodie& goodie, Player& player)
{
    player.setArmor(player.getTemplate()->armor());
}

} // end of namespace botlib
} // end of namespace mcdane
