#ifndef INCLUDED_COMMONLIB_TEXTURE_H
#define INCLUDED_COMMONLIB_TEXTURE_H

#include <string>
#include <commonlib_opengl.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

class Texture: public Object {
public:
    Texture();

    Texture(const std::string& imageFile);

    Texture(const Texture& other) = delete;

    virtual ~Texture();

    void init(const std::string& imageFile);

    bool valid() const
    {
        return id_ != 0;
    }

    GLuint id() const
    {
        return id_;
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return height_;
    }

    std::string toString() const override;

private:
    GLuint id_;
    int width_, height_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

