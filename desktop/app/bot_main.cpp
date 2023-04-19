#include <botlib_app_launcher.h>

int main(int argc, char *argv[])
{
    using namespace mcdane::botlib;

    AppLauncher launcher;
    launcher.init(argc, argv);
    launcher.run();
}
