#ifndef INCLUDED_BOTLIB_APP_ACTIONS_H
#define INCLUDED_BOTLIB_APP_ACTIONS_H

#include <functional>
#include <botlib_screen_type.h>

namespace mcdane {
namespace botlib {

using AppAction = std::function<void()>;
using SwitchScreenAction = std::function<void(ScreenType)>;

struct AppActions {
    AppAction exitAction_;
    SwitchScreenAction switchAction_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

