#include <sstream>
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
void Texture::init(const std::string &imageFile)
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

    unsigned char* data = stbi_load(imageFile.c_str(),
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
        THROW_EXCEPT(OpenGLException, "Failed to load image from " + imageFile);
    }

    stbi_image_free(data);
}
#elif __ANDROID__
void Texture::init(const std::string &imageFile) 
{
    AAsset *asset = AAssetManager_open(App::instance()->assetManager(),
                                    imageFile.c_str(),
                                    AASSET_MODE_BUFFER);

    AImageDecoder *decoder = nullptr;
    int result = AImageDecoder_createFromAAsset(asset, &decoder);
    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        THROW_EXCEPT(InvalidArgumentException, "Failed to open pic " + imageFile);
    }
    
    AImageDecoder_setAndroidBitmapFormat(decoder, ANDROID_BITMAP_FORMAT_RGBA_8888);

    const AImageDecoderHeaderInfo *header = AImageDecoder_getHeaderInfo(decoder);

    int width = AImageDecoderHeaderInfo_getWidth(header);
    int height = AImageDecoderHeaderInfo_getHeight(header);
    int stride = AImageDecoder_getMinimumStride(decoder);

    // Get the bitmap data of the image
    auto imageData = std::make_unique<std::vector<uint8_t>>(height * stride);
    result = AImageDecoder_decodeImage(decoder,imageData->data(), stride, imageData->size());
    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        THROW_EXCEPT(InvalidArgumentException, "Failed to decode pic " + imageFile);
    }

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
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