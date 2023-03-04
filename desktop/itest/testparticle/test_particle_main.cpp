#include <iostream>
#include <fstream>
#include <cstdlib>
#include <commonlib_argument_parser.h>
#include <commonlib_log.h>
#include <itest_test_particle_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::itest;

struct Arguments {
    std::string logFile_;
    std::string vertexShaderFile_;
    std::string fragShaderFile_;
    std::string textureFile_;
};

void parseArguments(Arguments& args, int argc, char* argv[])
{
    ArgumentParser parser;
    parser.init({
        Argument::create(args.logFile_, "logFile", "l", "log",
                         "Log file", false, k_nonEmptyStrV),
        Argument::create(args.vertexShaderFile_, "vertexShader", "v",
                         "vertexShader", "Vertex shader file",
                         false, k_nonEmptyStrV),
        Argument::create(args.fragShaderFile_, "fragShader", "f",
                         "fragShader", "Frag shader file",
                         false, k_nonEmptyStrV),
        Argument::create(args.textureFile_, "textureFile", "t",
                         "texture", "Texture file",
                         false, k_nonEmptyStrV)
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
        TestParticleApp app(args.vertexShaderFile_,
                            args.fragShaderFile_,
                            args.textureFile_);
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
