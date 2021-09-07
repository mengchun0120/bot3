#include <commonlib_log.h>
#include <botlib_graphics.h>

namespace mcdane {
namespace botlib {

std::shared_ptr<Graphics> Graphics::k_instance;

void Graphics::initInstance(const std::string& simpleVertexShaderFile,
                            const std::string& simpleFragShaderFile,
                            const std::string& fontDir)
{
    if (k_instance)
    {
        LOG_WARN << "Graphics instance already created" << LOG_END;
        return;
    }

    Graphics* g = new Graphics(simpleVertexShaderFile, simpleFragShaderFile,
                               fontDir);
    k_instance.reset(g);
}

Graphics::Graphics(const std::string& simpleVertexShaderFile,
                   const std::string& simpleFragShaderFile,
                   const std::string& fontDir)
{
    simpleShader_.init(simpleVertexShaderFile, simpleFragShaderFile);
    textSys_.load(fontDir);
}

} // end of namespace botlib
} // end of namespace mcdane

