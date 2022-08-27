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

    const TileTemplate* randomTileTemplate();

    const AIRobotTemplate* randoAIRobotTemplate();

    void addObj(GameMap& map,
                const GameObject* obj);

private:
    void initOccupied(int rowCount,
                      int colCount);

    void initTileTemplates();

    void initAIRobotTemplates();

    bool checkCollide(GameMap& map,
                      const commonlib::Vector2& pos,
                      float collideBreath);

protected:
    const GameLib& lib_;
    std::vector<const TileTemplate*> tileTemplates_;
    std::vector<const AIRobotTemplate*> aiRobotTemplates_;
    std::vector<std::vector<bool>> occupied_;
    commonlib::Random rand_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
