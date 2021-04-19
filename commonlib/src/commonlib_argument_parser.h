#ifndef INCLUDED_COMMONLIB_ARGUMENT_PARSER_H
#define INCLUDED_COMMONLIB_ARGUMENT_PARSER_H

#include <initializer_list>
#include <vector>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

class ArgumentParser {
public:
    ArgumentParser();

    ArgumentParser(std::initializer_list<Argument::Ptr> args);

    void Parse(int argc, const char * const argv[]);

private:
    std::vector<Argument::Ptr> args_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

