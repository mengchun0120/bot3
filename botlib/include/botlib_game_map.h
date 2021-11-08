#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <commonlib_vector.h>
#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

class GameMap {
public:
    static constexpr float k_cellBreath = 40.0f;
    static constexpr unsigned int k_minRows = 30;
    static constexpr unsigned int k_minCols = 40;

    inline static int getCellIdx(float x);

    GameMap();

    GameMap(unsigned int poolSize,
            unsigned int rows,
            unsigned int cols,
            float viewportWidth,
            float viewportHeight);

    ~GameMap();

    void init(unsigned int poolSize,
              unsigned int rows,
              unsigned int cols,
              float viewportWidth,
              float viewportHeight);

    void present() const;

    void addObj(GameObject* obj,
                GameObject::Deleter* deleter);

    inline int rowCount() const;

    inline int colCount() const;

    inline float width() const;

    inline float height() const;

    inline const commonlib::Vector2& getViewportOrigin() const;

    void setViewportOrigin(float x,
                           float y);

private:
    void initItemDeleter();

    void initPool(unsigned int poolSize);

    void initMap(unsigned int rows,
                 unsigned int cols,
                 float viewportWidth,
                 float viewportHeight);

    void setMapSize(unsigned int rows,
                    unsigned int cols);

    void setViewportSize(float viewportWidth,
                         float viewportHeight);

    void getPresentArea(int& startRow,
                        int& endRow,
                        int& startCol,
                        int& endCol) const;

private:
    using ItemList = commonlib::LinkedList<GameMapItem>;

private:
    ItemList::Deleter itemDeleter_;
    commonlib::ObjectPool<GameMapItem> itemPool_;
    std::vector<std::vector<ItemList>> map_;
    float width_;
    float height_;
    commonlib::Vector2 viewportSize_;
    commonlib::Vector2 viewportHalfSize_;
    commonlib::Vector2 minViewportOrigin_;
    commonlib::Vector2 maxViewportOrigin_;
    commonlib::Vector2 viewportOrigin_;
    commonlib::Vector2 viewportAnchor_;
    float maxObjWidth_;
    float maxObjHeight_;
};

int GameMap::getCellIdx(float x)
{
    return static_cast<int>(floor(x / k_cellBreath));
}

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
    return width_;
}

float GameMap::height() const
{
    return height_;
}

const commonlib::Vector2& GameMap::getViewportOrigin() const
{
    return viewportOrigin_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

