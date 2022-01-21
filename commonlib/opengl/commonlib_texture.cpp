#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_texture.h>

namespace mcdane {
namespace commonlib {

Texture::Texture()
    : id_(0)
    , width_(0)
    , height_(0)
{
}

Texture::Texture(const std::string& imageFile)
{
    init(imageFile);
}

Texture::~Texture()
{
    if (id_)
    {
        glDeleteTextures(1, &id_);
    }
}

void Texture::init(const std::string& imageFile)
{
    glGenTextures(1, &id_);
    if (id_ == 0)
    {
        THROW_EXCEPT(OpenGLException, "glGenTextures failed");
    }

    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int numChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(imageFile.c_str(), &width_, &height_,
                                    &numChannels, 0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        THROW_EXCEPT(OpenGLException, "Failed to load image from " + imageFile);
    }

    stbi_image_free(data);
}

rapidjson::Value Texture::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Texture", allocator);
    v.AddMember("id", id_, allocator);
    v.AddMember("width", width_, allocator);
    v.AddMember("height", height_, allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

} // end of namespace commonlib
} // end of namespace mcdane

