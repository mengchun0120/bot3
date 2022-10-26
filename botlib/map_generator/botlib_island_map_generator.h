#ifndef INCLUDED_BOTLIB_ISLAND_MAP_GENERATOR_H
#define INCLUDED_BOTLIB_ISLAND_MAP_GENERATOR_H

#include <memory>
#include <botlib_game_map_generator.h>

namespace mcdane {
namespace botlib {

class IslandMapGeneratorConfig;

class IslandMapGenerator: public GameMapGenerator {
public:
    IslandMapGenerator(const GameLib& lib,
                       std::shared_ptr<IslandMapGeneratorConfig> cfg);

    void generate(GameMap& map,
                  float viewportWidth,
                  float viewportHeight) override;

private:
    void addTiles(GameMap& map);

    void addIsland(GameMap& map,
                   const TileTemplate* t,
                   const commonlib::Vector2& startPos,
                   int tileCountX,
                   int tileCountY);

    float randomIslandBreath(float mapBreath, float base);

private:
    std::shared_ptr<IslandMapGeneratorConfig> cfg_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
