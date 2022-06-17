#ifndef INCLUDED_BOTLIB_TYPEDEF_H
#define INCLUDED_BOTLIB_TYPEDEF_H

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap;

template <typename T>
class LinkedList;

class Texture;

} // end of namespace commonlib
} // end of namespace mcdane

namespace mcdane {
namespace botlib {

class GameObject;
class Rectangle;
class ComponentTemplate;
class TileTemplate;
class MissileTemplate;
class GoodieTemplate;
class AIRobotTemplate;
class ParticleEffectTemplate;

using TextureLib = commonlib::NamedMap<commonlib::Texture>;
using RectLib = commonlib::NamedMap<Rectangle>;
using ComponentTemplateLib = commonlib::NamedMap<ComponentTemplate>;
using TileTemplateLib = commonlib::NamedMap<TileTemplate>;
using GoodieTemplateLib = commonlib::NamedMap<GoodieTemplate>;
using MissileTemplateLib = commonlib::NamedMap<MissileTemplate>;
using AIRobotTemplateLib = commonlib::NamedMap<AIRobotTemplate>;
using ParticleEffectTemplateLib = commonlib::NamedMap<ParticleEffectTemplate>;
using GameObjectList = commonlib::LinkedList<GameObject>;

} // end of namespace botlib
} // end of namespace mcdane

#endif

