#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_lib_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TextureLibParser::TextureLibParser(const std::string& picDir)
    : picDir_(picDir)
    , params_{jsonParam(fileName_, {"file"}, true, nonempty(fileName_))}
{
}

Texture* TextureLibParser::operator()(const rapidjson::Value& v)
{
    parse(params_, v);
    std::string path = constructPath({picDir_, fileName_});
    return new Texture(path);
}

RectLibParser::RectLibParser()
    : params_{
        jsonParam(width_, {"width"}, true, gt(width_, 0.0f)),
        jsonParam(height_, {"height"}, true, gt(height_, 0.0f)),
        jsonParam(hasTexture_, {"hasTexture"})
      }
{
}

Rectangle* RectLibParser::operator()(const rapidjson::Value& v)
{
    hasTexture_ = false;
    parse(params_, v);
    return hasTexture_ ? new Rectangle(width_, height_, TexRectangle()) :
                         new Rectangle(width_, height_);
}

GameObjectTemplateParser::GameObjectTemplateParser()
    : invincible_(false)
    , params_{
        jsonParam(width_, {"width"}, true, gt(width_, 0.0f)),
        jsonParam(height_, {"height"}, true, gt(height_, 0.0f)),
        jsonParam(collideBreath_, {"collideBreath"}, true,
                  ge(collideBreath_, 0.0f)),
        jsonParam(invincible_, {"invincible"}, false)
      }
{
}

void GameObjectTemplateParser::load(const rapidjson::Value& v)
{
    invincible_ = false;
    parse(params_, v);
}

TileTemplateLibParser::TileTemplateLibParser(
                            const NamedMap<commonlib::Texture>& textureLib,
                            const NamedMap<Rectangle>& rectLib)
    : textureLib_(textureLib)
    , rectLib_(rectLib)
    , params_{
        jsonParam(hp_, {"hp"}, true, ge(hp_, 0.0f)),
        jsonParam(textureName_, {"texture"}, true, nonempty(textureName_)),
        jsonParam(rectName_, {"rect"}, true, nonempty(rectName_))
      }
{
}

TileTemplate* TileTemplateLibParser::operator()(const rapidjson::Value& v)
{
    gameObjParser_.load(v);
    parse(params_, v);

    const Texture* texture = textureLib_.search(textureName_);
    if (!texture)
    {
        THROW_EXCEPT(ParseException, "Failed to find texture " + textureName_);
    }

    const Rectangle* rect = rectLib_.search(rectName_);
    if (!rect)
    {
        THROW_EXCEPT(ParseException, "Failed to find rectangle " + rectName_);
    }

    return new TileTemplate(gameObjParser_.width_,
                            gameObjParser_.height_,
                            gameObjParser_.collideBreath_,
                            hp_,
                            texture,
                            rect,
                            gameObjParser_.invincible_);
}

} // end of namespace botlib
} // end of namespace mcdane

