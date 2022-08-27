#include <commonlib_log.h>
#include <botlib_game_lib.h>
#include <botlib_game_map.h>
#include <botlib_island_map_generator_config.h>
#include <botlib_island_map_generator.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

IslandMapGenerator::IslandMapGenerator(const GameLib& lib,
                                       const IslandMapGeneratorConfig& cfg)
    : GameMapGenerator(lib)
    , cfg_(cfg)
{
}

void IslandMapGenerator::generate(GameMap& map,
                                  float viewportWidth,
                                  float viewportHeight)
{
    initMap(map, cfg_.rowCount(), cfg_.colCount(), viewportWidth, viewportHeight);
    addTiles(map);
    addPlayer(map);
    addAIRobots(map);
}

void IslandMapGenerator::addTiles(GameMap& map)
{
    
}

void IslandMapGenerator::addPlayer(GameMap& map)
{
}

void IslandMapGenerator::addAIRobots(GameMap& map)
{
}

void IslandMapGenerator::addIsland(GameMap& map,
                                   const TileTemplate* t,
                                   int islandWidth,
                                   int islandHeight)
{

}

} // end of namespace botlib
} // end of namespace mcdane
