#include <ctime>
#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_game_lib.h>
#include <botlib_player.h>
#include <botlib_ai_robot.h>
#include <botlib_game_map.h>
#include <botlib_game_map_generator_config.h>
#include <botlib_game_map_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameMapGenerator::CellCoord::init(int row,
                                       int col)
{
    row_ = row;
    col_ = col;
}

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

    initFreeCellMap(rowCount, colCount);
}

const TileTemplate* GameMapGenerator::randomTileTemplate(float maxCollideBreath)
{
    int maxIndex = findTileTemplate(maxCollideBreath);
    if (maxIndex < 0)
    {
        return nullptr;
    }

    int index = rand_.randomInt(0, maxIndex);

    return tileTemplates_[index];
}

const AIRobotTemplate* GameMapGenerator::randomAIRobotTemplate()
{
    int index = rand_.randomInt(0, aiRobotTemplates_.size() - 1);
    return aiRobotTemplates_[index];
}

void GameMapGenerator::addObj(GameMap& map,
                              GameObject* obj)
{
    int startRow = GameMap::getAbsCellIdx(obj->collideBottom());
    int endRow = GameMap::getAbsCellIdx(obj->collideTop());
    int startCol = GameMap::getAbsCellIdx(obj->collideLeft());
    int endCol = GameMap::getAbsCellIdx(obj->collideRight());

    for (int row = startRow; row <= endRow; ++row)
    {
        for (int col = startCol; col <= endCol; ++col)
        {
            int& curIndex = freeCellMap_[row][col];

            if (curIndex == -1)
            {
                continue;
            }

            if (curIndex != freeCellCount_ - 1)
            {
                CellCoord& lastCoord = freeCellCoords_[freeCellCount_-1];
                freeCellCoords_[curIndex] = lastCoord;
                freeCellMap_[lastCoord.row_][lastCoord.col_] = curIndex;
            }

            curIndex = -1;
            --freeCellCount_;
        }
    }

    map.addObj(obj);
}

Vector2 GameMapGenerator::getCellCenter(const CellCoord& coord)
{
    constexpr float MARGIN = GameMap::k_cellBreath / 2.0f;

    return Vector2{MARGIN + coord.col_ * GameMap::k_cellBreath,
                   MARGIN + coord.row_ * GameMap::k_cellBreath};
}

bool GameMapGenerator::findPlaceForObj(Vector2& pos,
                                       GameMap& map,
                                       const GameObjectTemplate* t)
{
    constexpr int MAX_TRIES = 20;
    int index = -1;
    Vector2 pos1;


    for (int tryCount = 0; tryCount < MAX_TRIES; ++tryCount)
    {
        index = rand_.randomInt(0, freeCellCount_-1);
        pos1 = getCellCenter(freeCellCoords_[index]);

        if (map.canBePlaced(pos1, t->collideBreath()))
        {
            break;
        }
    }

    if (index == -1)
    {
        return false;
    }

    pos = pos1;
    return true;
}

void GameMapGenerator::populateRobots(GameMap& map,
                                      int aiRobotCount)
{
    addPlayer(map);
    for (int i = 0; i < aiRobotCount; ++i)
    {
        addAIRobot(map);
    }
}

void GameMapGenerator::addPlayer(GameMap& map)
{
    Vector2 pos;
    const PlayerTemplate* t = &(lib_.playerTemplate());

    if (!findPlaceForObj(pos, map, t))
    {
        THROW_EXCEPT(MyException, "Failed to find place for player");
    }

    Vector2 direction = rand_.randomDirection();
    Player* player = new Player();
    player->init(t, pos, direction, 0.0f, 0.0f, 0.0f);
    addObj(map, player);
}

void GameMapGenerator::addAIRobot(GameMap& map)
{
    Vector2 pos;
    const AIRobotTemplate* t = randomAIRobotTemplate();

    if (!findPlaceForObj(pos, map, t))
    {
        THROW_EXCEPT(MyException, "Failed to find place for AI robot");
        return;
    }

    Vector2 direction = rand_.randomDirection();
    AIRobot* robot = new AIRobot();
    robot->init(t, pos, direction);
    addObj(map, robot);
}

void GameMapGenerator::initFreeCellMap(int rowCount,
                                       int colCount)
{
    freeCellCount_ = rowCount * colCount;
    freeCellMap_.resize(rowCount);
    freeCellCoords_.resize(freeCellCount_);
    for (int row = 0, index = 0; row < rowCount; ++row)
    {
        freeCellMap_[row].resize(colCount);
        for (int col = 0; col < colCount; ++col, ++index)
        {
            freeCellCoords_[index].init(row, col);
            freeCellMap_[row][col] = index;
        }
    }
}

void GameMapGenerator::initTileTemplates()
{
    lib_.tileTemplateLib().getAll(tileTemplates_);

    if (tileTemplates_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "No TileTemplate");
    }

    auto comparator = [](const TileTemplate*& t1,
                         const TileTemplate*& t2) -> bool
    {
        return t1->collideBreath() < t2->collideBreath();
    };

    std::sort(tileTemplates_.begin(), tileTemplates_.end(), comparator);
}

void GameMapGenerator::initAIRobotTemplates()
{
    lib_.aiRobotTemplateLib().getAll(aiRobotTemplates_);

    if (aiRobotTemplates_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "No AIRobotTemplate");
    }
}

int GameMapGenerator::findTileTemplate(float maxCollideBreath)
{
    int i;

    for (i = static_cast<int>(tileTemplates_.size()) - 1; i >= 0; --i)
    {
        if (tileTemplates_[i]->collideBreath() <= maxCollideBreath)
        {
            break;
        }
    }

    return i;
}

} // end of namespace botlib
} // end of namespace mcdane
