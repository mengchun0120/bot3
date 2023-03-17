#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_island_map_generator_config.h>
#include <botlib_island_map_generator.h>
#include <botlib_game_map_generator_factory.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapGenerator *GameMapGeneratorFactory::create(
                                    const std::string &algorithm,
                                    const GameLib &lib,
                                    const std::string &configFile)
{
    GameMapGenerator *generator = nullptr;

    if (algorithm == "island")
    {
        auto cfg = std::make_shared<IslandMapGeneratorConfig>(configFile);
        generator = new IslandMapGenerator(lib, cfg);
    }
    else
    {
        THROW_EXCEPT(InvalidArgumentException, "Unsupported algorithm " + algorithm);
    }

    return generator;
}

} // end of namespace botlib
} // end of namespace mcdane
