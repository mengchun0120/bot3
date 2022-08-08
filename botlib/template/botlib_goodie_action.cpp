#include <commonlib_log.h>
#include <botlib_goodie.h>
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
    float intervalMS = player.getTemplate()->fireIntervalMS() * t->factor();
    player.setFireIntervalMS(intervalMS);
}

void deactivateAttackAccelerator(Player& player)
{
    player.setFireIntervalMS(player.getTemplate()->fireIntervalMS());
}

void activateSpeedAccelerator(const GoodieTemplate* t,
                              Player& player)
{
    LOG_INFO << "SpeedAccel before activation speed="
             << player.speedNorm() << LOG_END;

    float speedNorm = player.getTemplate()->speed() * t->factor();
    player.setSpeedNorm(speedNorm);
    player.resetSpeed();

    LOG_INFO << "SpeedAccel after activation speed="
             << player.speedNorm() << LOG_END;

}

void deactivateSpeedAccelerator(Player& player)
{
    player.setSpeedNorm(player.getTemplate()->speed());
    player.resetSpeed();

    LOG_INFO << "SpeedAccel deactivated speed="
             << player.speedNorm() << LOG_END;
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
