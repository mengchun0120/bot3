#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

MyException::MyException(int line,
                         const std::string &file,
                         const std::string &msg) noexcept
    : line_(line)
    , file_(file)
{
    description_ = file_ + ":" + std::to_string(line_) + " " + msg;
}

const char *MyException::what() const noexcept
{
    return description_.c_str();
}

} // end of namespace commonlib
} // end of namespace mcdane

