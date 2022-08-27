#include <ctime>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_game_lib.h>
#include <botlib_game_map.h>
#include <botlib_game_map_generator_config.h>
#include <botlib_game_map_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapGenerator::GameMapGenerator(const GameLib& lib)
    : lib_(lib)
{
    initTileTemplates();
    initAIRobotTemplates();
}

void GameMapGenerator::initMap(GameMap& map,
                               int rowCount,
                               int colCount,
                               float viewportWidth,
                               float viewportHeight)
{
    map.init(rowCount, colCount,
             viewportWidth, viewportHeight,
             lib_.maxObjSpan(), lib_.maxCollideBreath());

    initOccupied(rowCount, colCount);
}

const TileTemplate* GameMapGenerator::randomTileTemplate()
{
    int index = rand_.randomInt(0, tileTemplates_.size() - 1);
    return tileTemplates_[index];
}

const AIRobotTemplate* GameMapGenerator::randoAIRobotTemplate()
{
    int index = rand_.randomInt(0, aiRobotTemplates_.size() - 1);
    return aiRobotTemplates_[index];
}

void GameMapGenerator::initOccupied(int rowCount,
                                    int colCount)
{
    occupied_.resize(rowCount);
    for (auto& row: occupied_)
    {
        row.resize(colCount);
    }
}

void GameMapGenerator::initTileTemplates()
{
    lib_.tileTemplateLib().getAll(tileTemplates_);
}

void GameMapGenerator::initAIRobotTemplates()
{
    lib_.aiRobotTemplateLib().getAll(aiRobotTemplates_);
}

bool checkCollide(GameMap& map,
                      const commonlib::Vector2& pos,
                      float collideBreath);


} // end of namespace botlib
} // end of namespace mcdane
