#ifndef INCLUDED_BOTLIB_GAME_OBJ_UPDATER_H
#define INCLUDED_BOTLIB_GAME_OBJ_UPDATER_H

namespace mcdane {
namespace botlib {

class GameObject;
class UpdateContext;

class GameObjUpdater {
public:
    GameObjUpdater() = default;

    void init(UpdateContext *cxt);

    bool operator()(GameObject *obj);

private:
    UpdateContext *cxt_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
