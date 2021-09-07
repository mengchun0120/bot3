#ifndef INCLUDED_BOTLIB_GRAPHICS_H
#define INCLUDED_BOTLIB_GRAPHICS_H

#include <memory>
#include <botlib_simple_shader_program.h>
#include <botlib_text_system.h>

namespace mcdane {
namespace botlib {

class Graphics {
public:
    inline static Graphics& getInstance();

    static void initInstance(const std::string& simpleVertexShaderFile,
                             const std::string& simpleFragShaderFile,
                             const std::string& fontDir);

    ~Graphics() = default;

    inline SimpleShaderProgram& simpleShader();

    inline TextSystem& textSys();

private:
    Graphics(const std::string& simpleVertexShaderFile,
             const std::string& simpleFragShaderFile,
             const std::string& fontDir);

private:
    static std::shared_ptr<Graphics> k_instance;

    SimpleShaderProgram simpleShader_;
    TextSystem textSys_;
};

Graphics& Graphics::getInstance()
{
    return *k_instance;
}

SimpleShaderProgram& Graphics::simpleShader()
{
    return simpleShader_;
}

TextSystem& Graphics::textSys()
{
    return textSys_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

