#ifndef INCLUDED_COMMONLIB_BOT_APP_H
#define INCLUDED_COMMONLIB_BOT_APP_H

#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {

class BotApp: public App {
public:
    BotApp();

    ~BotApp() override;

    bool preProcess() override;

    bool process() override;

    bool postProcess() override;

private:
    void initApp();

#ifdef DESKTOP_APP
    void initWindow();
#endif

    void setupOpenGL();
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

