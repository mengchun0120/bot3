#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

Screen::Screen(const AppActions& actions)
{
    init(actions);
}

void Screen::init(const AppActions& actions)
{
    actions_ = actions;
}

} // end of namespace botlib
} // end of namespace mcdane

