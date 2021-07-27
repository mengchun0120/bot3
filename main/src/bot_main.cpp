#include <iostream>
#include <fstream>
#include <cstdlib>
#include <commonlib_argument_parser.h>
#include <commonlib_log.h>
#include <commonlib_app_config.h>
#include <commonlib_app.h>

using namespace mcdane::commonlib;

struct Arguments {
    std::string configFile_;
};

void parseArguments(Arguments& args, int argc, char* argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args.configFile_, "configFile", "c", "config",
                         "Config file", false, nonempty(args.configFile_))
    });

    parser.parse(argc, argv);
}

void initLog()
{
    static std::ofstream os;
    const AppConfig& cfg = AppConfig::getInstance();

    os.open(cfg.logFile());

    if (!os.good())
    {
        THROW_EXCEPT(FileException, "Failed to open file " + cfg.logFile());
    }

    Logger::initInstance(os, Logger::LEVEL_DEBUG);
}

int main(int argc, char* argv[])
{
    Arguments args;

    try
    {
        parseArguments(args, argc, argv);
        AppConfig::initInstance(args.configFile_);
        initLog();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception happened while initializing app: " << e.what()
                  << std::endl;
        exit(1);
    }

    LOG_INFO << "Initialization complete" << LOG_END;
}
