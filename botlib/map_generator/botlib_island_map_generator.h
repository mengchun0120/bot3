#ifndef INCLUDED_BOTLIB_ISLAND_MAP_GENERATOR_H
#define INCLUDED_BOTLIB_ISLAND_MAP_GENERATOR_H

#include <botlib_game_map_generator.h>

namespace mcdane {
namespace botlib {

class IslandMapGeneratorConfig;

class IslandMapGenerator: public GameMapGenerator {
public:
    IslandMapGenerator(const GameLib& lib,
                       const IslandMapGeneratorConfig& cfg);

    void generate(GameMap& map,
                  float viewportWidth,
                  float viewportHeight) override;

private:
    void addTiles(GameMap& map);

    void addPlayer(GameMap& map);

    void addAIRobots(GameMap& map);

    void addIsland(GameMap& map,
                   const TileTemplate* t,
                   int islandWidth,
                   int islandHeight);

private:
    const IslandMapGeneratorConfig& cfg_;
    
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
