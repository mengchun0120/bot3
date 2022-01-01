#ifndef INCLUDED_BOTLIB_TYPEDEF_H
#define INCLUDED_BOTLIB_TYPEDEF_H

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap;
class Texture;

} // end of namespace commonlib
} // end of namespace mcdane

namespace mcdane {
namespace botlib {

class Rectangle;
class ComponentTemplate;
class TileTemplate;
class MissileTemplate;
class AIRobotTemplate;
class ParticleEffectTemplate;

using TextureLib = commonlib::NamedMap<commonlib::Texture>;
using RectLib = commonlib::NamedMap<Rectangle>;
using ComponentTemplateLib = commonlib::NamedMap<ComponentTemplate>;
using TileTemplateLib = commonlib::NamedMap<TileTemplate>;
using MissileTemplateLib = commonlib::NamedMap<MissileTemplate>;
using AIRobotTemplateLib = commonlib::NamedMap<AIRobotTemplate>;
using ParticleEffectTemplateLib = commonlib::NamedMap<ParticleEffectTemplate>;

} // end of namespace botlib
} // end of namespace mcdane

#endif

