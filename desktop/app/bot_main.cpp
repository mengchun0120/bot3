#include <botlib_app_launcher.h>

int main(int argc, char *argv[])
{
    using namespace mcdane::botlib;

    AppLauncher launcher;
    launcher.init(argc - 1, argv + 1);
    launcher.run();
}
