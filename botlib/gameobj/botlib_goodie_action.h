#ifndef INCLUDED_BOTLIB_GOODIE_ACTION_H
#define INCLUDED_BOTLIB_GOODIE_ACTION_H

#include <functional>

namespace mcdane {
namespace botlib {

class Goodie;
class Player;
class UpdateContext;

using ActivateGoodieAction =
            std::function<void(const GoodieTemplate*,
                               Player&)>;

using DeactivateGoodieAction = std::function<void(Player&)>;

void activateHealthFiller(const GoodieTemplate* t,
                          Player& player);

void activateAttackAccelerator(const GoodieTemplate* t,
                               Player& player);

void deactivateAttackAccelerator(Player& player);

void activateSpeedAccelerator(const GoodieTemplate* t,
                              Player& player);

void deactivateSpeedAccelerator(Player& player);

void activateDamageAmplifier(const GoodieTemplate* t,
                             Player& player);

void deactivateDamageAmplifier(Player& player);

void activateGodMode(const GoodieTemplate* t,
                     Player& player);

void deactivateGodMode(Player& player);

} // end of namespace botlib
} // end of namespace mcdane

#endif

