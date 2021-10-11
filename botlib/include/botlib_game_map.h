#ifndef INCLUDED_BOTLIB_GAME_MAP_H
#define INCLUDED_BOTLIB_GAME_MAP_H

#include <vector>
#include <functional>
#include <cmath>
#include <commonlib_vector.h>
#include <commonlib_linked_list.h>
#include <commonlib_object_pool.h>
#include <botlib_game_map_item.h>

namespace mcdane {
namespace botlib {

class GameMap {
public:
    static constexpr float k_cellBreath = 50.0f;

    inline static int getCellIdx(float x);

    GameMap();

    GameMap(unsigned int poolSize,
            unsigned int rows,
            unsigned int cols,
            float viewportWidth,
            float viewportHeight,
            float originX,
            float originY);

    ~GameMap();

    void init(unsigned int poolSize,
              unsigned int rows,
              unsigned int cols,
              float viewportWidth,
              float viewportHeight,
              float originX,
              float originY);

    void present() const;

    void addObj(GameObject* obj,
                GameObject::Deleter* deleter);

    inline int rowCount() const;

    inline int colCount() const;

    inline float width() const;

    inline float height() const;

    void setOrigin(float originX,
                   float originY);

private:
    void initItemDeleter();

    void initPool(unsigned int poolSize);

    void initMap(unsigned int rows,
                 unsigned int cols,
                 float viewportWidth,
                 float viewportHeight,
                 float originX,
                 float originY);

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
    float viewportWidth_;
    float viewportHeight_;
    float maxOriginX_;
    float maxOriginY_;
    float originX_;
    float originY_;
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

} // end of namespace botlib
} // end of namespace mcdane

#endif

