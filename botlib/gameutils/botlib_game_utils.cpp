#include <fstream>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_game_lib.h>
#include <botlib_game_utils.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void loadGameMap(GameMap& map,
                 const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);
}

} // end of namespace botlib
} // end of namespace mcdane

