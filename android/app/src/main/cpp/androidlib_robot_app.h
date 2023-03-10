#ifndef INCLUDED_ANDROIDLIB_ROBOT_APP_H
#define INCLUDED_ANDROIDLIB_ROBOT_APP_H

#include <commonlib_app.h>

namespace mcdane {
namespace androidlib {

class RobotApp : public mcdane::commonlib::App {
public:
    RobotApp();

    ~RobotApp() override;

    bool init(android_app* app);

    void process() override;
};

} // end of namespace androidlib
} // end of namespace mcdane

#endif
