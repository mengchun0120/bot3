#ifndef INCLUDED_BOTLIB_GAME_MAP_GENERATOR_H
#define INCLUDED_BOTLIB_GAME_MAP_GENERATOR_H

#include <vector>
#include <commonlib_random.h>
#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class GameMap;
class GameLib;
class TileTemplate;
class AIRobotTemplate;

class GameMapGenerator {
public:
    struct CellCoord {
        CellCoord() = default;

        void init(int row,
                  int col);

        int row_;
        int col_;
    };

public:
    GameMapGenerator(const GameLib& lib);

    virtual ~GameMapGenerator() = default;

    virtual void generate(GameMap& map,
                          float viewportWidth,
                          float viewportHeight) = 0;
protected:
    void initMap(GameMap& map,
                 int rowCount,
                 int colcount,
                 float viewportWidth,
                 float viewportHeight);

    const TileTemplate* randomTileTemplate(float maxCollideBreath);

    const AIRobotTemplate* randomAIRobotTemplate();

    void addObj(GameMap& map,
                GameObject* obj);

    commonlib::Vector2 getCellCenter(const CellCoord& coord);

    bool findPlaceForObj(commonlib::Vector2& pos,
                         GameMap& map,
                         const GameObjectTemplate* t);

    void populateRobots(GameMap& map,
                        int aiRobotCount);

    void addPlayer(GameMap& map);

    void addAIRobot(GameMap& map);

private:
    void initFreeCellMap(int rowCount,
                         int colCount);

    void initTileTemplates();

    void initAIRobotTemplates();

    int findTileTemplate(float maxCollideBreath);

protected:
    const GameLib& lib_;
    std::vector<const TileTemplate*> tileTemplates_;
    std::vector<const AIRobotTemplate*> aiRobotTemplates_;
    std::vector<std::vector<int>> freeCellMap_;
    std::vector<CellCoord> freeCellCoords_;
    int freeCellCount_;
    commonlib::Random rand_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
