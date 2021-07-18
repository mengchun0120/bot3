#include <sstream>
#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

MyException::MyException(int line,
                         const char* file,
                         const char* msg) noexcept:
    line_(line),
    file_(file),
    msg_(msg)
{
    description_ = file_ + ":" + std::to_string(line_) + " " + msg_;
}

MyException::MyException(int line,
                         const char* file,
                         const std::string& msg) noexcept:
    MyException(line, file, msg.c_str())
{
}

const char* MyException::what() const noexcept
{
    return description_.c_str();
}

} // end of namespace commonlib
} // end of namespace mcdane

