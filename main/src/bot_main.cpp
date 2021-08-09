#include <iostream>
#include <fstream>
#include <cstdlib>
#include <commonlib_argument_parser.h>
#include <commonlib_log.h>
#include <commonlib_app_config.h>
#include <commonlib_bot_app.h>

using namespace mcdane::commonlib;

struct Arguments {
    std::string configFile_;
    std::string logFile_;
};

void parseArguments(Arguments& args, int argc, char* argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args.configFile_, "configFile", "c", "config",
                         "Config file", false, nonempty(args.configFile_)),
        Argument::create(args.logFile_, "logFile", "l", "log",
                         "Log file", false, nonempty(args.logFile_))
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
        BotApp::initInstance(args.configFile_);
        BotApp::getInstance().run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << "Exception happened while running: " << e.what()
                  << LOG_END;
        exit(1);
    }

    exit(0);
}
