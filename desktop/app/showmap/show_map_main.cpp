#include <iostream>
#include <fstream>
#include <cstdlib>
#include <commonlib_argument_parser.h>
#include <commonlib_log.h>
#include <botlib_show_map_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

struct Arguments {
    std::string appConfigFile_;
    std::string logLevelStr_;
    std::string logFile_;
    std::string mapFile_;
    std::string appDir_;
};

void parseArguments(Arguments& args, int argc, char* argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args.appConfigFile_,
                         "appConfig",
                         "c",
                         "appConfig",
                         "Config file for app",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args.logFile_,
                         "logFile",
                         "l",
                         "logFile",
                         "Log file",
                         false,
                         k_nonEmptyStrV),
        Argument::create(args.logLevelStr_,
                         "logLevel",
                         "v",
                         "logLevel",
                         "Log level",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args.mapFile_,
                         "mapFile",
                         "m",
                         "mapFile",
                         "File to store generated map",
                         true,
                         k_nonEmptyStrV),
        Argument::create(args.appDir_,
                         "appDir",
                         "a",
                         "appDir",
                         "App directory",
                         false,
                         k_nonEmptyStrV)
    });

    parser.parse(argc, argv);
}

void initLog(const std::string& logLevelStr,
             const std::string& logFile)
{
    static std::ofstream os;

    os.open(logFile);

    if (!os.good())
    {
        THROW_EXCEPT(FileException, "Failed to open file " + logFile);
    }

    Logger::LogLevel level = Logger::LEVEL_DEBUG;

    if (!logLevelStr.empty())
    {
        level = Logger::strToLevel(logLevelStr);
    }

    Logger::initInstance(os, level);
}


int main(int argc,
         char* argv[])
{
    Arguments args;

    try
    {
        parseArguments(args, argc, argv);
        initLog(args.logLevelStr_, args.logFile_);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception happened while initializing app: " << e.what()
                  << std::endl;
        exit(1);
    }

    LOG_INFO << "Initialization complete " << args.appDir_
             << " " << args.mapFile_ << LOG_END;

    try
    {
        ShowMapApp app;
        app.init(args.appConfigFile_, args.appDir_, args.mapFile_);
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