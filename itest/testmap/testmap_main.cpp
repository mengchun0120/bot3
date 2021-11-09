#include <iostream>
#include <fstream>
#include <cstdlib>
#include <commonlib_argument_parser.h>
#include <commonlib_log.h>
#include <itest_testmap_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::itest;

struct Arguments {
    std::string configFile_;
    std::string logFile_;
    std::string appDir_;
    std::string mapFile_;
};

void parseArguments(Arguments& args, int argc, char* argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args.configFile_, "configFile", "c", "config",
                         "Config file", false, nonempty(args.configFile_)),
        Argument::create(args.logFile_, "logFile", "l", "log",
                         "Log file", false, nonempty(args.logFile_)),
        Argument::create(args.appDir_, "appDir", "a", "appDir",
                         "App directory", false, nonempty(args.appDir_)),
        Argument::create(args.mapFile_, "mapFile", "m", "mapFile",
                         "Map file", false, nonempty(args.mapFile_))
    });

    parser.parse(argc, argv);
}

void initLog(const std::string& logFile)
{
    static std::ofstream os;

    os.open(logFile);

    if (!os.good())
    {
        THROW_EXCEPT(FileException, "Failed to open file " + logFile);
    }

    Logger::initInstance(os, Logger::LEVEL_DEBUG);
}

int main(int argc, char* argv[])
{
    Arguments args;

    try
    {
        parseArguments(args, argc, argv);
        initLog(args.logFile_);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception happened while initializing app: " << e.what()
                  << std::endl;
        exit(1);
    }

    LOG_INFO << "Initialization complete" << LOG_END;

    try
    {
        TestMapApp app(args.configFile_, args.appDir_, args.mapFile_);
        app.run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << "Exception happened while running: " << e.what()
                  << LOG_END;
        exit(1);
    }

    exit(0);
}
