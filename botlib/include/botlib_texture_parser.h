#ifndef INCLUDED_BOTLIB_TEXTURE_PARSER_H
#define INCLUDED_BOTLIB_TEXTURE_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <commonlib_texture.h>

namespace mcdane {
namespace botlib {

class TextureParser {
public:
    TextureParser(const std::string& picDir);

    commonlib::Texture* operator()(const rapidjson::Value& v);

private:
    std::string picDir_;
    std::string fileName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

