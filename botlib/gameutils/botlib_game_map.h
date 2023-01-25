#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <initializer_list>
#include <rapidjson/document.h>
#include <commonlib_vector.h>
#include <commonlib_linked_list.h>
#include <commonlib_region.h>
#include <botlib_game_object.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameMapAccessor;
class Player;

class GameMap: public commonlib::Object {
private:
    static constexpr int k_layerCount = 4;

    using Cell = std::array<GameObjectList, k_layerCount>;

public:
    static constexpr unsigned int k_minRows = 30;
    static constexpr unsigned int k_minCols = 30;
    static constexpr float k_cellBreath = 40.0f;

    enum Layer {
        LAYER_TILE_GOODIE,
        LAYER_ROBOT,
        LAYER_MISSILE,
        LAYER_EFFECT
    };

    static const Layer k_objLayerMap[k_gameObjTypeCount];

public:
    inline static int getLayer(GameObjectType type);

    inline static int getAbsCellIdx(float x);

    GameMap() = default;

    ~GameMap() = default;

    void init(unsigned int rows,
              unsigned int cols,
              float viewportWidth,
              float viewportHeight,
              float maxObjSpan,
              float maxCollideBreath,
              GameObjDeleter objDeleter = nullptr);

    void present();

    void addObj(GameObject* obj);

    void repositionObj(GameObject* obj);

    void removeObj(GameObject* obj);

    void unlinkObj(GameObject* obj);

    inline int rowCount() const;

    inline int colCount() const;

    inline int absRowCount() const;

    inline int absColCount() const;

    inline float width() const;

    inline float height() const;

    inline const commonlib::Vector2& viewportOrigin() const;

    inline const commonlib::Vector2& viewportAnchor() const;

    inline const commonlib::Region<float>& boundary() const;

    inline const commonlib::Region<float>& viewableRegion() const;

    inline const commonlib::Region<int>& presentArea() const;

    inline const commonlib::Region<int> wholeArea() const;

    inline int getCellIdx(float x) const;

    inline const Player* player() const;

    inline Player* player();

    inline int aiRobotCount() const;

    inline const std::string& aiRobotCountStr() const;

    void setViewportOrigin(float x, float y);

    void setViewportOrigin(const commonlib::Vector2& p);

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r,
                                          float deltaX,
                                          float deltaY) const;

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r) const;

    commonlib::Region<int> getCoverArea(const commonlib::Region<float>& r) const;

    template <typename F>
    void traverse(const commonlib::Region<int>& r,
                  F& accessor,
                  int startLayer=0,
                  int layerCount=k_layerCount);

    template <typename F>
    void traverse(const commonlib::Region<int>& r,
                  F& accessor,
                  std::initializer_list<int> layers);

    template <typename F>
    bool traverseLayer(const commonlib::Region<int>& r,
                       F& accessor,
                       int layer);

    inline bool canSee(const GameObject* obj) const;

    bool checkCollision(commonlib::Vector2& delta,
                        const GameObject* obj);

    bool canBePlaced(const commonlib::Vector2& pos,
                     float collideBreath);

    void toJson(rapidjson::Document& doc);

private:
    void initObjDeleter();

    void initMapCells(unsigned int rows,
                      unsigned int cols,
                      GameObjDeleter objDeleter);

    void setBoundary(unsigned int rows, unsigned int cols);

    void setViewportSize(float viewportWidth, float viewportHeight);

    void resetViewableRegion();

    void resetPresentArea();

    void presentObjs();

    void presentParticleEffects();

    bool checkNonpassthroughCollide(commonlib::Vector2& delta,
                                    const GameObject* obj);

    std::string detail();

    void updateAIRobotCountStr();

private:
    float maxObjSpan_;
    float maxCollideBreath_;
    int extraCell_;
    std::vector<std::vector<Cell>> cells_;
    commonlib::Vector2 viewportSize_;
    commonlib::Vector2 viewportHalfSize_;
    commonlib::Vector2 minViewportOrigin_;
    commonlib::Vector2 maxViewportOrigin_;
    commonlib::Vector2 viewportOrigin_;
    commonlib::Vector2 viewportAnchor_;
    commonlib::Region<float> boundary_;
    commonlib::Region<float> viewableRegion_;
    commonlib::Region<int> presentArea_;
    Player* player_;
    int aiRobotCount_;
    std::string aiRobotCountStr_;
};

int GameMap::getLayer(GameObjectType type)
{
    return k_objLayerMap[static_cast<int>(type)];
}

int GameMap::getAbsCellIdx(float x)
{
    return static_cast<int>(floor(x / k_cellBreath));
}

int GameMap::rowCount() const
{
    return static_cast<int>(cells_.size());
}

int GameMap::colCount() const
{
    return static_cast<int>(cells_[0].size());
}

int GameMap::absRowCount() const
{
    return rowCount() - extraCell_ * 2;
}

int GameMap::absColCount() const
{
    return colCount() - extraCell_ * 2;
}

float GameMap::width() const
{
    return boundary_.right();
}

float GameMap::height() const
{
    return boundary_.top();
}

const commonlib::Vector2& GameMap::viewportOrigin() const
{
    return viewportOrigin_;
}

const commonlib::Vector2& GameMap::viewportAnchor() const
{
    return viewportAnchor_;
}

const commonlib::Region<float>& GameMap::boundary() const
{
    return boundary_;
}

const commonlib::Region<float>& GameMap::viewableRegion() const
{
    return viewableRegion_;
}

const commonlib::Region<int>& GameMap::presentArea() const
{
    return presentArea_;
}

const commonlib::Region<int> GameMap::wholeArea() const
{
    return commonlib::Region<int>{0, colCount()-1, 0, rowCount()-1};
}

int GameMap::getCellIdx(float x) const
{
    return getAbsCellIdx(x) + extraCell_;
}

const Player* GameMap::player() const
{
    return player_;
}

Player* GameMap::player()
{
    return player_;
}

int GameMap::aiRobotCount() const
{
    return aiRobotCount_;
}

const std::string& GameMap::aiRobotCountStr() const
{
    return aiRobotCountStr_;
}

bool GameMap::canSee(const GameObject* obj) const
{
    return presentArea_.contains(obj->col(), obj->row());
}

template <typename F>
void GameMap::traverse(const commonlib::Region<int>& r,
                       F& accessor,
                       int startLayer,
                       int layerCount)
{
    int endLayer = startLayer + layerCount - 1;

    for (int layer = startLayer; layer <= endLayer; ++layer)
    {
        if (!traverseLayer(r, accessor, layer))
        {
            return;
        }
    }
}

template <typename F>
void GameMap::traverse(const commonlib::Region<int>& r,
                       F& accessor,
                       std::initializer_list<int> layers)
{
    for (auto it = layers.begin(); it != layers.end(); ++it)
    {
        if (!traverseLayer(r, accessor, *it))
        {
            return;
        }
    }
}

template <typename F>
bool GameMap::traverseLayer(const commonlib::Region<int>& r,
                            F& accessor,
                            int layer)
{
    for (int rowIdx = r.bottom(); rowIdx <= r.top(); ++rowIdx)
    {
        auto& row = cells_[rowIdx];
        for (int colIdx = r.left(); colIdx <= r.right(); ++colIdx)
        {
            GameObjectList& objs = row[colIdx][layer];
            GameObject* next;
            for (GameObject* obj = objs.first(); obj; obj = next)
            {
                next = obj->next();
                if (!accessor(obj))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

