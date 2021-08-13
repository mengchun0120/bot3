#ifndef INCLUDED_COMMONLIB_JSON_UTILS_H
#define INCLUDED_COMMONLIB_JSON_UTILS_H

#include <string>
#include <vector>
#include <rapidjson/document.h>

namespace mcdane {
namespace commonlib {

void readJson(rapidjson::Document& doc,
              const std::string& fileName);

const rapidjson::Value* findJson(const rapidjson::Document& doc,
                                 const std::vector<std::string>& path);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
