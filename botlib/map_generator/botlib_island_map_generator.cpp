#include <algorithm>
#include <commonlib_log.h>
#include <botlib_game_lib.h>
#include <botlib_game_map.h>
#include <botlib_tile.h>
#include <botlib_island_map_generator_config.h>
#include <botlib_island_map_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

IslandMapGenerator::IslandMapGenerator(const GameLib &lib,
                                       std::shared_ptr<IslandMapGeneratorConfig> cfg)
    : GameMapGenerator(lib)
    , cfg_(cfg)
{
    if (!cfg_)
    {
        THROW_EXCEPT(InvalidArgumentException, "cfg is null");
    }
}

void IslandMapGenerator::generate(GameMap &map,
                                  float viewportWidth,
                                  float viewportHeight)
{
    LOG_INFO << "Starting" << LOG_END;
    initMap(map, cfg_->rowCount(), cfg_->colCount(), viewportWidth, viewportHeight);
    LOG_INFO << "Map initialized" << LOG_END;
    addTiles(map);
    LOG_INFO << "Tiles finished" << LOG_END;
    populateRobots(map, cfg_->aiRobotCount());
    LOG_INFO << "Robots finished" << LOG_END;
}

void IslandMapGenerator::addTiles(GameMap &map)
{
    float baseY = rand_.randomFloat(cfg_->minIslandDist(), cfg_->maxIslandDist());
    float maxBaseY = map.height() - cfg_->minIslandBreath() - cfg_->minIslandDist();
    float maxBaseX = map.width() - cfg_->minIslandBreath() - cfg_->minIslandDist();

    while (baseY <=  maxBaseY)
    {
        float baseX = rand_.randomFloat(cfg_->minIslandDist(),
                                        cfg_->maxIslandDist());
        float maxIslandHeight = 0.0f;

        while (baseX <= maxBaseX)
        {
            float islandBreathX = randomIslandBreath(map.width(), baseX);
            float islandBreathY = randomIslandBreath(map.height(), baseY);
            float maxCollideBreath = std::min(islandBreathX, islandBreathY) / 2.0f;

            const TileTemplate *t = randomTileTemplate(maxCollideBreath);
            if (!t)
            {
                LOG_WARN << "No matching TileTemplate found maxCollideBreath="
                         << maxCollideBreath << LOG_END;
                break;
            }

            float tileBreath = t->collideBreath() * 2.0f;
            int tileCountX = static_cast<int>(floor(islandBreathX / tileBreath));
            int tileCountY = static_cast<int>(floor(islandBreathY / tileBreath));
            Vector2 startPos{baseX + t->collideBreath(),
                             baseY + t->collideBreath()};

            LOG_INFO << "baseX=" << baseX
                     << " baseY=" << baseY
                     << " t=" << t->name()
                     << " startPos=" << startPos
                     << " tileCountX=" << tileCountX
                     << " tileCountY=" << tileCountY << LOG_END;

            addIsland(map, t, startPos, tileCountX, tileCountY);

            float islandHeight = tileCountY * tileBreath;
            if (islandHeight > maxIslandHeight)
            {
                maxIslandHeight = islandHeight;
            }

            float islandWidth = tileCountX * tileBreath;
            float distX = rand_.randomFloat(cfg_->minIslandDist(),
                                            cfg_->maxIslandDist());
            baseX += islandWidth + distX;
        }

        float distY = rand_.randomFloat(cfg_->minIslandDist(),
                                        cfg_->maxIslandDist());
        baseY += maxIslandHeight + distY;
    }
}

void IslandMapGenerator::addIsland(GameMap &map,
                                   const TileTemplate *t,
                                   const Vector2 &startPos,
                                   int tileCountX,
                                   int tileCountY)
{
    float delta = 2.0f * t->collideBreath();
    Vector2 pos;
    Vector2 direction{1.0f, 0.0f};

    pos[1] = startPos[1];
    for (int row = 0; row < tileCountY; ++row, pos[1] += delta)
    {
        pos[0] = startPos[0];
        for (int col = 0; col < tileCountX; ++col, pos[0] += delta)
        {
            Tile *tile = new Tile();
            tile->init(t, pos, direction);
            addObj(map, tile);
        }
    }
}

float IslandMapGenerator::randomIslandBreath(float mapBreath, float base)
{

    float maxBreath = std::min(mapBreath - cfg_->minIslandDist() - base,
                               cfg_->maxIslandBreath());
    return rand_.randomFloat(cfg_->minIslandBreath(), maxBreath);
}

} // end of namespace botlib
} // end of namespace mcdane
