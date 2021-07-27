#include <commonlib_app.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP
void App::run()
{
    while (true)
    {
        process();
    }
}
#endif

void App::process()
{
}

} // end of namespace commonlib
} // end of namespace mcdane

