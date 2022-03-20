#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_graphics.h>

namespace mcdane {
namespace botlib {

std::shared_ptr<Graphics> Graphics::k_instance;

void Graphics::initInstance(const AppConfig& cfg)
{
    if (k_instance)
    {
        LOG_WARN << "Graphics instance already created" << LOG_END;
        return;
    }

    Graphics* g = new Graphics(cfg);
    k_instance.reset(g);
}

Graphics::Graphics(const AppConfig& cfg)
{
    simpleShader_.init(cfg.simpleVertexShaderFiles(),
                       cfg.simpleFragShaderFiles());
    particleShader_.init(cfg.particleVertexShaderFiles(),
                         cfg.particleFragShaderFiles());
    textSys_.load(cfg.fontDir());
}

} // end of namespace botlib
} // end of namespace mcdane

