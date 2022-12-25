#ifndef INCLUDED_BOTLIB_TYPEDEF_H
#define INCLUDED_BOTLIB_TYPEDEF_H

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap;

template <typename T>
class LinkedItem;

template <typename T>
class LinkedList;

template <typename T>
class ObjectPool;

class Texture;
class VertexArray;

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
class ProgressPieTemplate;
class ProgressBarTemplate;
class IconTemplate;

using TextureLib = commonlib::NamedMap<commonlib::Texture>;
using VertexArrayLib = commonlib::NamedMap<commonlib::VertexArray>;
using RectLib = commonlib::NamedMap<Rectangle>;
using ComponentTemplateLib = commonlib::NamedMap<ComponentTemplate>;
using TileTemplateLib = commonlib::NamedMap<TileTemplate>;
using GoodieTemplateLib = commonlib::NamedMap<GoodieTemplate>;
using MissileTemplateLib = commonlib::NamedMap<MissileTemplate>;
using AIRobotTemplateLib = commonlib::NamedMap<AIRobotTemplate>;
using ParticleEffectTemplateLib = commonlib::NamedMap<ParticleEffectTemplate>;
using ProgressPieTemplateLib = commonlib::NamedMap<ProgressPieTemplate>;
using ProgressBarTemplateLib = commonlib::NamedMap<ProgressBarTemplate>;
using IconTemplateLib = commonlib::NamedMap<IconTemplate>;
using GameObjectList = commonlib::LinkedList<GameObject>;
using GameObjectItem = commonlib::LinkedItem<GameObject*>;
using GameObjectItemPool = commonlib::ObjectPool<GameObjectItem>;

} // end of namespace botlib
} // end of namespace mcdane

#endif

