#include <ctime>
#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_region.h>
#include <commonlib_math_utils.h>
#include <botlib_game_lib.h>
#include <botlib_player.h>
#include <botlib_ai_robot.h>
#include <botlib_game_map.h>
#include <botlib_game_map_generator_config.h>
#include <botlib_game_map_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

namespace {

int getMapCellRowIdx(GameMap& map, int y)
{
    return clamp(GameMap::getAbsCellIdx(y), 0, map.absRowCount() - 1);
}

int getMapCellColIdx(GameMap& map, int x)
{
    return clamp(GameMap::getAbsCellIdx(x), 0, map.absColCount() - 1);
}

} // end of unnamed namespace

void GameMapGenerator::CellCoord::init(int row, int col)
{
    row_ = row;
    col_ = col;
}

GameMapGenerator::GameMapGenerator(const GameLib& lib)
    : lib_(lib)
{
    initTileTemplates();
    initAIRobotTemplates();
    initCellMarker();
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

void GameMapGenerator::addObj(GameMap& map, GameObject* obj)
{
    markObjOccupied(map, obj);
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

void GameMapGenerator::populateRobots(GameMap& map, int aiRobotCount)
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
        LOG_WARN << "Failed to find place for robot " << t->name() << LOG_END;
        return;
    }

    Vector2 direction = rand_.randomDirection();
    AIRobot* robot = new AIRobot();
    robot->init(t, pos, direction);
    addObj(map, robot);
}

void GameMapGenerator::initFreeCellMap(int rowCount, int colCount)
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

void GameMapGenerator::initCellMarker()
{
    using namespace std::placeholders;

    cellMarker_ = std::bind(&GameMapGenerator::markCellOccupied, this, _1, _2);
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

void GameMapGenerator::markObjOccupied(GameMap& map, GameObject* obj)
{
    Region<int> region{
        getMapCellColIdx(map, obj->collideLeft()),
        getMapCellColIdx(map, obj->collideRight()),
        getMapCellRowIdx(map, obj->collideBottom()),
        getMapCellRowIdx(map, obj->collideTop())
    };
    region.iterate(cellMarker_, 1, 1);
}

bool GameMapGenerator::markCellOccupied(int col, int row)
{
    int& curIndex = freeCellMap_[row][col];

    if (curIndex == -1)
    {
        return true;
    }

    if (curIndex != freeCellCount_ - 1)
    {
        CellCoord& lastCoord = freeCellCoords_[freeCellCount_-1];
        freeCellCoords_[curIndex] = lastCoord;
        freeCellMap_[lastCoord.row_][lastCoord.col_] = curIndex;
    }

    curIndex = -1;
    --freeCellCount_;
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
