#include <sstream>
#include <algorithm>
#ifdef DESKTOP_APP
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#elif __ANDROID__
#include <android/imagedecoder.h>
#endif
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_system.h>
#include <commonlib_app.h>
#include <commonlib_texture.h>

namespace mcdane {
namespace commonlib {

Texture::~Texture()
{
    if (id_)
    {
        glDeleteTextures(1, &id_);
    }
}

#ifdef DESKTOP_APP
void Texture::init(const std::string &path)
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

    unsigned char* data = stbi_load(path.c_str(),
                                    &width_,
                                    &height_,
                                    &numChannels,
                                    0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width_,
                     height_,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        THROW_EXCEPT(OpenGLException, "Failed to load image from " + path);
    }

    stbi_image_free(data);
}
#elif __ANDROID__
void flipImage(uint8_t *data, int height, int stride)
{
    uint8_t *row1 = data, *row2 = data + (height-1) * stride;
    while(row1 < row2)
    {
        std::swap_ranges(row1, row1+stride, row2);
        row1 += stride;
        row2 -= stride;
    }
}

void Texture::init(const std::string &path)
{
    AAsset *asset = AAssetManager_open(assetManager(),
                                       path.c_str(),
                                       AASSET_MODE_BUFFER);
    if (!asset)
    {
        THROW_EXCEPT(FileException, "Failed to open pic " + path);
    }

    AImageDecoder *decoder = nullptr;

    int result = AImageDecoder_createFromAAsset(asset, &decoder);
    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        THROW_EXCEPT(OpenGLException, "Failed get decoder");
    }

    AImageDecoder_setAndroidBitmapFormat(decoder, ANDROID_BITMAP_FORMAT_RGBA_8888);

    const AImageDecoderHeaderInfo *header = AImageDecoder_getHeaderInfo(decoder);
    if (!header)
    {
        THROW_EXCEPT(OpenGLException, "Failed to get header");
    }

    width_ = AImageDecoderHeaderInfo_getWidth(header);
    height_ = AImageDecoderHeaderInfo_getHeight(header);
    int stride = AImageDecoder_getMinimumStride(decoder);

    auto imageData = std::make_unique<std::vector<uint8_t>>(height_ * stride);
    result = AImageDecoder_decodeImage(decoder, imageData->data(),
                                       stride, imageData->size());

    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        THROW_EXCEPT(InvalidArgumentException, "Failed to decode pic " + path);
    }

    flipImage(imageData->data(), height_, stride);

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, imageData->data());

    glGenerateMipmap(GL_TEXTURE_2D);

    AImageDecoder_delete(decoder);
    AAsset_close(asset);
}
#endif

void Texture::init(const rapidjson::Value &v,
                   const std::string &picDir)
{
    std::string fileName;

    std::vector<JsonParamPtr> params{
        jsonParam(fileName, "file", true, k_nonEmptyStrV)
    };

    parse(params, v);

    fileName = constructPath({picDir, fileName});
    init(fileName);
}

} // end of namespace commonlib
} // end of namespace mcdane
