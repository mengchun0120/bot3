#ifndef INCLUDED_BOTLIB_GRAPHICS_H
#define INCLUDED_BOTLIB_GRAPHICS_H

#include <memory>
#include <botlib_simple_shader_program.h>
#include <botlib_particle_shader_program.h>
#include <botlib_text_system.h>

namespace mcdane {
namespace botlib {

class AppConfig;

class Graphics {
public:
    inline static SimpleShaderProgram& simpleShader();

    inline static ParticleShaderProgram& particleShader();

    inline static TextSystem& textSys();

    static void initInstance(const AppConfig& cfg);

    Graphics(const AppConfig& cfg);

    ~Graphics() = default;

private:
    static std::shared_ptr<Graphics> k_instance;

    SimpleShaderProgram simpleShader_;
    ParticleShaderProgram particleShader_;
    TextSystem textSys_;
};

SimpleShaderProgram& Graphics::simpleShader()
{
    return k_instance->simpleShader_;
}

TextSystem& Graphics::textSys()
{
    return k_instance->textSys_;
}

ParticleShaderProgram& Graphics::particleShader()
{
    return k_instance->particleShader_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

