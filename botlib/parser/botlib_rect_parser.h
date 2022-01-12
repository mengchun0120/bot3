#ifndef INCLUDED_BOTLIB_RECT_PARSER_H
#define INCLUDED_BOTLIB_RECT_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>

namespace mcdane {
namespace botlib {

class Rectangle;

class RectParser {
public:
    RectParser();

    Rectangle* operator()(const rapidjson::Value& v);

private:
    float width_;
    float height_;
    bool hasTexture_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

