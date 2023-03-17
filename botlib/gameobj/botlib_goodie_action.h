#ifndef INCLUDED_BOTLIB_GOODIE_ACTION_H
#define INCLUDED_BOTLIB_GOODIE_ACTION_H

#include <functional>
#include <botlib_goodie_type.h>

namespace mcdane {
namespace botlib {

class Player;
class GoodieTemplate;

void activateGoodie(const GoodieTemplate *t, Player &player);

void deactivateGoodie(GoodieType type, Player &player);

} // end of namespace botlib
} // end of namespace mcdane

#endif

