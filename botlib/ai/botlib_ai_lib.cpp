#include <commonlib_log.h>
#include <botlib_ai_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AILib::init(const std::string &chaseShootAIParamFile)
{
    initChaseShootAIParamLib(chaseShootAIParamFile);
}

void AILib::initChaseShootAIParamLib(const std::string &chaseShootAIParamFile)
{
    auto parser = [](ChaseShootAIParam &param,
                     const std::string &name,
                     const rapidjson::Value &v)
    {
        param.init(v);
    };

    chaseShootAIParamLib_.init(chaseShootAIParamFile, parser);

    LOG_INFO << "ChaseShootAIParamLib initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

