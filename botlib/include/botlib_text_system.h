#ifndef INCLUDED_BOTLIB_TEXT_SYSTEM_H
#define INCLUDED_BOTLIB_TEXT_SYSTEM_H

#include <vector>
#include <commonlib_texture.h>
#include <botlib_simple_shader_program.h>
#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

class TextSystem {
public:
    static const int MIN_CHAR = 32;
    static const int MAX_CHAR = 126;
    static const int CHAR_COUNT = MAX_CHAR - MIN_CHAR + 1;

    TextSystem() = default;

    ~TextSystem() = default;

    void load(const std::string& fontDir);

    void draw(SimpleShaderProgram& program,
              const std::string& s,
              const commonlib::Point2& pos,
              TextSize size,
              const commonlib::Color* color=nullptr);

private:
    std::vector<commonlib::Texture> fonts_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

