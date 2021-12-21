#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <commonlib_vector.h>
#include <commonlib_linked_list.h>
#include <commonlib_region.h>
#include <commonlib_object_pool.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

class GameMap {
public:
    using ItemList = commonlib::LinkedList<GameMapItem>;
    using Accessor = std::function<bool(GameObject*)>;

public:
    static constexpr float k_cellBreath = 40.0f;
    static constexpr unsigned int k_minRows = 30;
    static constexpr unsigned int k_minCols = 40;

    GameMap() = default;

    ~GameMap() = default;

    void init(unsigned int poolSize,
              unsigned int rows,
              unsigned int cols,
              float viewportWidth,
              float viewportHeight,
              float maxObjSpan,
              float maxCollideBreath);

    void present();

    void addObj(GameObject* obj,
                GameObject::Deleter* deleter=&GameObject::k_defaultDeleter);

    void repositionObj(GameObject* o);

    inline int rowCount() const;

    inline int colCount() const;

    inline float width() const;

    inline float height() const;

    inline const commonlib::Region<float>& boundary() const;

    inline const commonlib::Vector2& getViewportOrigin() const;

    inline int getCellIdx(float x) const;

    void setViewportOrigin(float x,
                           float y);

    GameMapItem* searchObj(GameObject* o);

    GameMapItem* unlinkObj(GameObject* o);

    void getCollideArea(int& startRow,
                        int& endRow,
                        int& startCol,
                        int& endCol,
                        float left,
                        float right,
                        float bottom,
                        float top,
                        float deltaX,
                        float deltaY) const;

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r,
                                          float deltaX,
                                          float deltaY) const;

    void getCollideArea(int& startRow,
                        int& endRow,
                        int& startCol,
                        int& endCol,
                        float left,
                        float right,
                        float bottom,
                        float top) const;

    commonlib::Region<int> getCollideArea(const commonlib::Region<float>& r) const;

    void accessRegion(int startRow,
                      int endRow,
                      int startCol,
                      int endCol,
                      Accessor& accessor);

    void accessRegion(const commonlib::Region<int>& r,
                      Accessor& accessor);

    bool checkRectCollide(float left,
                          float right,
                          float bottom,
                          float top) const;

private:
    void initItemDeleter();

    void initPool(unsigned int poolSize);

    void initMap(unsigned int rows,
                 unsigned int cols,
                 float viewportWidth,
                 float viewportHeight,
                 float maxObjSpan,
                 float maxCollideBreath);

    void setBoundary(unsigned int rows,
                     unsigned int cols);

    void setViewportSize(float viewportWidth,
                         float viewportHeight);

    void getPresentArea(int& startRow,
                        int& endRow,
                        int& startCol,
                        int& endCol) const;

    void presentCell(const ItemList& cell,
                     GameObjectType type) const;

private:
    ItemList::Deleter itemDeleter_;
    commonlib::ObjectPool<GameMapItem> itemPool_;
    std::vector<std::vector<ItemList>> map_;
    commonlib::Region<float> boundary_;
    commonlib::Vector2 viewportSize_;
    commonlib::Vector2 viewportHalfSize_;
    commonlib::Vector2 minViewportOrigin_;
    commonlib::Vector2 maxViewportOrigin_;
    commonlib::Vector2 viewportOrigin_;
    commonlib::Vector2 viewportAnchor_;
    float maxObjSpan_;
    float maxCollideBreath_;
};

int GameMap::rowCount() const
{
    return static_cast<int>(map_.size());
}

int GameMap::colCount() const
{
    return static_cast<int>(map_[0].size());
}

float GameMap::width() const
{
    return boundary_.right();
}

float GameMap::height() const
{
    return boundary_.top();
}

const commonlib::Region<float>& GameMap::boundary() const
{
    return boundary_;
}

const commonlib::Vector2& GameMap::getViewportOrigin() const
{
    return viewportOrigin_;
}

int GameMap::getCellIdx(float x) const
{
    return static_cast<int>(floor(x / k_cellBreath));
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

