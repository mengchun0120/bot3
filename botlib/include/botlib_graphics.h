#ifndef INCLUDED_BOTLIB_GRAPHICS_H
#define INCLUDED_BOTLIB_GRAPHICS_H

#include <memory>
#include <botlib_simple_shader_program.h>
#include <botlib_particle_shader_program.h>
#include <botlib_text_system.h>

namespace mcdane {
namespace botlib {

class Graphics {
public:
    inline static SimpleShaderProgram& simpleShader();

    inline static ParticleShaderProgram& particleShader();

    inline static TextSystem& textSys();

    static void initInstance(
                        const std::vector<std::string>& simpleVertexShaderFiles,
                        const std::vector<std::string>& simpleFragShaderFiles,
                        const std::vector<std::string>& particleVertexShaderFiles,
                        const std::vector<std::string>& particleFragShaderFiles,
                        const std::string& fontDir);

    ~Graphics() = default;

private:
    Graphics(const std::vector<std::string>& simpleVertexShaderFiles,
             const std::vector<std::string>& simpleFragShaderFiles,
             const std::vector<std::string>& particleVertexShaderFiles,
             const std::vector<std::string>& particleFragShaderFiles,
             const std::string& fontDir);

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

