#include <ctime>
#include <algorithm>
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

void GameMapGenerator::addObj(GameMap& map,
                              const GameObject* obj)
{
    int startRow = GameMap::getAbsCellIdx(obj->collideBottom());
    int endRow = GameMap::getAbsCellIdx(obj->collideTop());
    int startCol = GameMap::getAbsCellIdx(obj->collideLeft());
    int endCol = GameMap::getAbsCellIdx(obj->collideRight());

    for (int r = startRow; r <= endRow; ++r)
    {
        for (int c = startCol; c <= endCol; ++c)
        {
            occupied_[r][c] = true;
        }
    }
}

void GameMapGenerator::initOccupied(int rowCount,
                                    int colCount)
{
    occupied_.resize(rowCount);
    for (auto it = occupied_.begin(); it != occupied_.end(); ++it)
    {
        it->resize(colCount);
        std::fill(it->begin(), it->end(), false);
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

} // end of namespace botlib
} // end of namespace mcdane
