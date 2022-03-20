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
    static void initInstance(const AppConfig& cfg);

    inline static Graphics& getInstance();

    Graphics(const AppConfig& cfg);

    ~Graphics() = default;

    inline SimpleShaderProgram& simpleShader();

    inline ParticleShaderProgram& particleShader();

    inline const TextSystem& textSys() const;

private:
    static std::shared_ptr<Graphics> k_instance;

    SimpleShaderProgram simpleShader_;
    ParticleShaderProgram particleShader_;
    TextSystem textSys_;
};

Graphics& Graphics::getInstance()
{
    return *k_instance;
}

SimpleShaderProgram& Graphics::simpleShader()
{
    return k_instance->simpleShader_;
}

ParticleShaderProgram& Graphics::particleShader()
{
    return k_instance->particleShader_;
}

const TextSystem& Graphics::textSys() const
{
    return k_instance->textSys_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

