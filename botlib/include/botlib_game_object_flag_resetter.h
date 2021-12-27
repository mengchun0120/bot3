#ifndef INCLUDED_BOTLIB_GAME_OBJECT_FLAG_RESETTER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_FLAG_RESETTER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class GameObjectFlagResetter: public GameMapAccessor {
public:
    void reset(GameObject::Flag flag,
               bool value);

    bool run(ItemList& itemList,
             GameMapItem* item) override;

private:
    GameObject::Flag flag_;
    bool value_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

