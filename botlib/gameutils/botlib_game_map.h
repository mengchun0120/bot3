#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <rapidjson/document.h>
#include <commonlib_vector.h>
#include <commonlib_linked_list.h>
#include <commonlib_region.h>
#include <botlib_game_object.h>
#include <botlib_game_object_presenter.h>
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

    inline static int getAbsCellIdx(float x);

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

    void setViewportOrigin(float x, float y);

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r,
                                          float deltaX,
                                          float deltaY) const;

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r) const;

    void accessRegion(const commonlib::Region<int>& r,
                      GameMapAccessor& accessor,
                      int startLayer=0,
                      int layerCount=k_layerCount);

    inline bool canSee(const GameObject* obj) const;

    bool checkCollision(commonlib::Vector2& delta,
                        const GameObject* obj);

    void decreaseAIRobotCount();

    bool canBePlaced(const commonlib::Vector2& pos,
                     float collideBreath);

    void toJson(rapidjson::Document& doc);

private:
    void initObjDeleter();

    void initMapCells(unsigned int rows, unsigned int cols);

    void setBoundary(unsigned int rows, unsigned int cols);

    void setViewportSize(float viewportWidth, float viewportHeight);

    void resetViewableRegion();

    void resetPresentArea();

    void presentObjs();

    void presentParticleEffects();

    bool checkNonpassthroughCollide(commonlib::Vector2& delta,
                                    const GameObject* obj);

    std::string detail();

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
    GameObjectPresenter objPresenter_;
};

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

bool GameMap::canSee(const GameObject* obj) const
{
    return presentArea_.contains(obj->col(), obj->row());
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

