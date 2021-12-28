#include <commonlib_log.h>
#include <botlib_graphics.h>

namespace mcdane {
namespace botlib {

std::shared_ptr<Graphics> Graphics::k_instance;

void Graphics::initInstance(
                    const std::vector<std::string>& simpleVertexShaderFiles,
                    const std::vector<std::string>& simpleFragShaderFiles,
                    const std::vector<std::string>& particleVertexShaderFiles,
                    const std::vector<std::string>& particleFragShaderFiles,
                    const std::string& fontDir)
{
    if (k_instance)
    {
        LOG_WARN << "Graphics instance already created" << LOG_END;
        return;
    }

    Graphics* g = new Graphics(simpleVertexShaderFiles,
                               simpleFragShaderFiles,
                               particleVertexShaderFiles,
                               particleFragShaderFiles,
                               fontDir);
    k_instance.reset(g);
}

Graphics::Graphics(const std::vector<std::string>& simpleVertexShaderFiles,
                   const std::vector<std::string>& simpleFragShaderFiles,
                   const std::vector<std::string>& particleVertexShaderFiles,
                   const std::vector<std::string>& particleFragShaderFiles,
                   const std::string& fontDir)
{
    simpleShader_.init(simpleVertexShaderFiles, simpleFragShaderFiles);
    particleShader_.init(particleVertexShaderFiles, particleFragShaderFiles);
    textSys_.load(fontDir);
}

} // end of namespace botlib
} // end of namespace mcdane

