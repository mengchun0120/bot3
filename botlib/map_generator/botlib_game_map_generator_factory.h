#ifndef INCLUDED_BOTLIB_GAME_MAP_GENERATOR_FACTORY_H
#define INCLUDED_BOTLIB_GAME_MAP_GENERATOR_FACTORY_H

#include <string>

namespace mcdane {
namespace botlib {

class GameLib;
class GameMapGenerator;

class GameMapGeneratorFactory {
public:
    static GameMapGenerator* create(const std::string& algorithm,
                                    const GameLib& lib,
                                    const std::string& configFile);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
