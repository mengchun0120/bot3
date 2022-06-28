#ifndef INCLUDED_BOTLIB_GOODIE_ACTION_H
#define INCLUDED_BOTLIB_GOODIE_ACTION_H

#include <functional>

namespace mcdane {
namespace botlib {

class Goodie;
class Player;

using GoodieAction = std::function<void(Goodie&, Player&)>;

void activateHealthFiller(Goodie& goodie, Player& player);

void activateAttackAccelerator(Goodie& goodie, Player& player);

void deactivateAttackAccelerator(Goodie& goodie, Player& player);

void activateSpeedAccelerator(Goodie& goodie, Player& player);

void deactivateSpeedAccelerator(Goodie& goodie, Player& player);

void activateDamageAmplifier(Goodie& goodie, Player& player);

void deactivateDamageAmplifier(Goodie& goodie, Player& player);

void activateArmorEnhancer(Goodie& goodie, Player& player);

void deactivateArmorEnhancer(Goodie& goodie, Player& player);

} // end of namespace botlib
} // end of namespace mcdane

#endif

