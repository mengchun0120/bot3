#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <string>
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
public:
    static constexpr int k_layerCount = 4;

    using Cell = std::array<GameObjectList, k_layerCount>;

    static constexpr float k_cellBreath = 40.0f;
    static constexpr unsigned int k_minRows = 30;
    static constexpr unsigned int k_minCols = 40;

public:

    static int getLayer(GameObjectType type);

    GameMap() = default;

    ~GameMap() = default;

    void init(unsigned int rows,
              unsigned int cols,
              float viewportWidth,
              float viewportHeight,
              float maxObjSpan,
              float maxCollideBreath);

    void present();

    void addObj(GameObject* obj);

    void repositionObj(GameObject* obj);

    void removeObj(GameObject* obj);

    void unlinkObj(GameObject* obj);

    inline int rowCount() const;

    inline int colCount() const;

    inline float width() const;

    inline float height() const;

    inline const commonlib::Vector2& viewportOrigin() const;

    inline const commonlib::Vector2& viewportAnchor() const;

    inline const commonlib::Region<float>& boundary() const;

    inline const commonlib::Region<float>& viewableRegion() const;

    inline const commonlib::Region<int>& presentArea() const;

    inline int getCellIdx(float x) const;

    inline const Player* player() const;

    inline Player* player();

    void setViewportOrigin(float x,
                           float y);

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r,
                                          float deltaX,
                                          float deltaY) const;

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r) const;

    void accessRegion(const commonlib::Region<int>& r,
                      GameMapAccessor& accessor,
                      int startLayer=0,
                      int layerCount=k_layerCount);

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

    inline bool canSee(const GameObject* obj) const;

private:
    void initObjDeleter();

    void initMapCells(unsigned int rows,
                      unsigned int cols);

    void setBoundary(unsigned int rows,
                     unsigned int cols);

    void setViewportSize(float viewportWidth,
                         float viewportHeight);

    void resetViewableRegion();

    void resetPresentArea();

    void presentObjs();

    void presentParticleEffects();

    rapidjson::Value cellsToJson(
                rapidjson::Document::AllocatorType& allocator) const;

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
};

int GameMap::rowCount() const
{
    return static_cast<int>(cells_.size());
}

int GameMap::colCount() const
{
    return static_cast<int>(cells_[0].size());
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

int GameMap::getCellIdx(float x) const
{
    return static_cast<int>(floor(x / k_cellBreath)) + extraCell_;
}

const Player* GameMap::player() const
{
    return player_;
}

Player* GameMap::player()
{
    return player_;
}

bool GameMap::canSee(const GameObject* obj) const
{
    return presentArea_.contains(obj->col(), obj->row());
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

