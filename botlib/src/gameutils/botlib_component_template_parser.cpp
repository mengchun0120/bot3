#include <commonlib_exception.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>
#include <botlib_component_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentTemplateParser::ComponentTemplateParser(
                            const TextureLib& textureLib,
                            const RectLib& rectLib)
    : textureLib_(textureLib)
    , rectLib_(rectLib)
    , params_{
        jsonParam(textureName_, "texture", true, k_nonEmptyStrV),
        jsonParam(rectName_, "rect", true, k_nonEmptyStrV)
      }
{
}

ComponentTemplate* ComponentTemplateParser::operator()(const rapidjson::Value& v)
{
    parse(params_, v);

    const Texture* texture = textureLib_.search(textureName_);
    if (!texture)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find texture " + textureName_);
    }

    const Rectangle* rect = rectLib_.search(rectName_);
    if (!rect)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find rect " + rectName_);
    }

    return new ComponentTemplate(texture, rect);
}

} // end of namespace botlib
} // end of namespace mcdane

