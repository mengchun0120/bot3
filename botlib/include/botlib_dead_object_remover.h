#ifndef INCLUDED_BOTLIB_DEAD_OBJECT_REMOVER_H
#define INCLUDED_BOTLIB_DEAD_OBJECT_REMOVER_H

#include <botlib_game_map_accessor.h>

namespace mcdane {
namespace botlib {

class DeadObjectRemover: public GameMapAccessor {
public:
    bool run(ItemList& itemList,
             GameMapItem* item) override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

