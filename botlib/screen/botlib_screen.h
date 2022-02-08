#ifndef INCLUDED_BOTLIB_SCREEN_H
#define INCLUDED_BOTLIB_SCREEN_H

#include <commonlib_input_event.h>
#include <botlib_app_actions.h>

namespace mcdane {
namespace botlib {

class Screen {
public:
    Screen(const AppActions& actions);

    virtual ~Screen() = default;

    virtual void update() = 0;

    virtual void present() = 0;

    virtual bool processInput(const commonlib::InputEvent &e) = 0;

protected:
    AppActions actions_;
};


} // end of namespace botlib
} // end of namespace mcdane

#endif

