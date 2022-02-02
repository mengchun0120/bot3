#ifndef INCLUDED_COMMONLIB_TEXTURE_H
#define INCLUDED_COMMONLIB_TEXTURE_H

#include <string>
#include <commonlib_opengl.h>
#include <commonlib_named_object.h>

namespace mcdane {
namespace commonlib {

class Texture: public NamedObject {
public:
    Texture() = default;

    ~Texture() override;

    void init(const std::string& imageFile);

    void init(const rapidjson::Value& v,
              const std::string& picDir,
              bool requireName = true);

    inline bool valid() const;

    inline GLuint id() const;

    inline int width() const;

    inline int height() const;

    rapidjson::Value toJson(
        rapidjson::Document::AllocatorType& allocator) const override;

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

