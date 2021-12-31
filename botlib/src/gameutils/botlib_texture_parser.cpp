#include <commonlib_file_utils.h>
#include <botlib_texture_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TextureParser::TextureParser(const std::string& picDir)
    : picDir_(picDir)
    , params_{jsonParam(fileName_, "file", true, k_nonEmptyStrV)}
{
}

Texture* TextureParser::operator()(const rapidjson::Value& v)
{
    parse(params_, v);
    std::string path = constructPath({picDir_, fileName_});
    return new Texture(path);
}

} // end of namespace botlib
} // end of namespace mcdane

