#ifndef INCLUDED_COMMONLIB_TEXTURE_H
#define INCLUDED_COMMONLIB_TEXTURE_H

#include <string>
#include <commonlib_opengl.h>
#include <commonlib_named_object.h>

namespace mcdane {
namespace commonlib {

class Texture {
public:
    Texture() = default;

    ~Texture();

    void init(const std::string &path);

    void init(const rapidjson::Value &v,
              const std::string &picDir);

    inline bool valid() const;

    inline GLuint id() const;

    inline int width() const;

    inline int height() const;

private:
    GLuint id_;
    int width_, height_;
};

bool Texture::valid() const
{
    return id_ != 0;
}

GLuint Texture::id() const
{
    return id_;
}

int Texture::width() const
{
    return width_;
}

int Texture::height() const
{
    return height_;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
