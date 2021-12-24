#include <utility>
#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_lib_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TextureParser::TextureParser(const std::string& picDir)
    : picDir_(picDir)
    , params_{jsonParam(fileName_, "file", true, k_nonEmptyStrV)}
{
}

Texture* TextureParser::operator()(const rapidjson::Value& v)
{
    parse(params_, v);
    std::string path = constructPath({picDir_, fileName_});
    return new Texture(path);
}

RectParser::RectParser()
    : params_{
        jsonParam(width_, "width", true, gt(0.0f)),
        jsonParam(height_, "height", true, gt(0.0f)),
        jsonParam(hasTexture_, "hasTexture")
      }
{
}

Rectangle* RectParser::operator()(const rapidjson::Value& v)
{
    hasTexture_ = false;
    parse(params_, v);
    return hasTexture_ ? new Rectangle(width_, height_, TexRectangle()) :
                         new Rectangle(width_, height_);
}

ComponentTemplateParser::ComponentTemplateParser(
                            const NamedMap<Texture>& textureLib,
                            const NamedMap<Rectangle>& rectLib)
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

ComponentParser::ComponentParser(
        const NamedMap<ComponentTemplate>& componentLib)
    : componentLib_(componentLib)
    , params_{
        jsonParam(templateName_, "template", true, k_nonEmptyStrV),
        jsonParam(pos_, "pos"),
        jsonParam(direction_, "direction")
      }
{
}

void ComponentParser::initComponent(Component& c,
                                    const rapidjson::Value& v)
{
    parse(params_, v);

    ComponentTemplate* t = componentLib_.search(templateName_);
    if (!t)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find ComponentTemplate " + templateName_);
    }

    c.init(t, pos_, direction_);
}

GameObjectTemplateParser::GameObjectTemplateParser()
    : invincible_(false)
    , params_{
        jsonParam(collideBreath_, "collideBreath", true, ge(0.0f)),
        jsonParam(invincible_, "invincible", false)
      }
{
}

void GameObjectTemplateParser::load(const rapidjson::Value& v)
{
    invincible_ = false;
    parse(params_, v);
}

CompositeObjectTemplateParser::CompositeObjectTemplateParser(
                    const NamedMap<ComponentTemplate>& componentLib)
    : componentParser_(componentLib)
{
}

void CompositeObjectTemplateParser::load(const rapidjson::Value& v)
{
    GameObjectTemplateParser::load(v);

    const rapidjson::Value* a = findJson(v, {"components"});
    if (!a)
    {
        THROW_EXCEPT(ParseException, "Failed to find components");
    }

    if (!a->IsArray())
    {
        THROW_EXCEPT(ParseException, "components is not array");
    }

    if (a->Capacity() == 0)
    {
        THROW_EXCEPT(ParseException, "components is empty");
    }

    components_.resize(a->Capacity());
    for (unsigned int i = 0; i < a->Capacity(); ++i)
    {
        componentParser_.initComponent(components_[i], (*a)[i]);
    }
}

TileTemplateParser::TileTemplateParser(
                        const NamedMap<ComponentTemplate>& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(hp_, "hp", true, ge(0.0f))
      }
{
}

TileTemplate* TileTemplateParser::operator()(const rapidjson::Value& v)
{
    load(v);
    parse(params_, v);

    return new TileTemplate(collideBreath_,
                            hp_,
                            invincible_,
                            std::move(components_));
}

MissileTemplateParser::MissileTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(damage_, "damage", true, gt(0.0f)),
        jsonParam(speed_, "speed", true, gt(0.0f))
      }
{
}

MissileTemplate* MissileTemplateParser::operator()(const rapidjson::Value& v)
{
    CompositeObjectTemplateParser::load(v);
    parse(params_, v);

    return new MissileTemplate(collideBreath_,
                               damage_,
                               speed_,
                               std::move(components_));
}

RobotTemplateParser::RobotTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(hp_, "hp", true, ge(0.0f)),
        jsonParam(armor_, "armor", true, ge(0.0f)),
        jsonParam(energy_, "energy", true, ge(0.0f)),
        jsonParam(speed_, "speed", true, ge(0.0f)),
        jsonParam(rechargeRate_, "rechargeRate", true, ge(0.0f)),
        jsonParam(fireIntervalMS_, "fireIntervalMS", true, gt(0.0f)),
        jsonParam(firePoints_, "firePoints", true,
                  nonempty<std::vector<commonlib::Vector2>>()),
        jsonParam(fireDirections_, "fireDirections", true,
                  nonempty<std::vector<commonlib::Vector2>>())
      }
{
}

void RobotTemplateParser::load(const rapidjson::Value& v)
{
    CompositeObjectTemplateParser::load(v);
    parse(params_, v);

    if (firePoints_.size() != fireDirections_.size())
    {
        THROW_EXCEPT(ParseException,
                     "firePoints size doens't match fireDirections size");
    }
}

AIRobotTemplateParser::AIRobotTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib)
    : RobotTemplateParser(componentTemplateLib)
{
}

AIRobotTemplate* AIRobotTemplateParser::operator()(const rapidjson::Value& v)
{
    RobotTemplateParser::load(v);

    return new AIRobotTemplate(hp_, armor_, speed_, energy_, rechargeRate_,
                               collideBreath_, fireIntervalMS_,
                               std::move(components_),
                               std::move(firePoints_),
                               std::move(fireDirections_));
}

} // end of namespace botlib
} // end of namespace mcdane

