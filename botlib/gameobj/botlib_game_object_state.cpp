#include <commonlib_exception.h>
#include <botlib_game_object_state.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::GameObjectState state)
{
    using namespace mcdane::botlib;

    switch(state)
    {
        case GameObjectState::ALIVE:
            return os << "alive";
        case GameObjectState::DYING:
            return os << "dying";
        case GameObjectState::DEAD:
            return os << "dead";
        case GameObjectState::DUMPED:
            return os << "dumped";
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid state");
    }
}

} // end of namespace std

