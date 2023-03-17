#ifndef INCLUDED_COMMONLIB_INPUT_MAP_H
#define INCLUDED_COMMONLIB_INPUT_MAP_H

#include <string>
#include <unordered_map>

namespace mcdane {
namespace commonlib {

class InputMap {
public:
    InputMap();

    int get(const std::string &name) const;

private:
    void init();

private:
    std::unordered_map<std::string, int> map_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif
