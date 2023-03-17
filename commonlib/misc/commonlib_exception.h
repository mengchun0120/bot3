#ifndef INCLUDED_COMMONLIB_EXCEPTION_H
#define INCLUDED_COMMONLIB_EXCEPTION_H

#include <exception>
#include <string>

namespace mcdane {
namespace commonlib {

class MyException: public std::exception {
public:
    MyException(int line,
                const std::string &file,
                const std::string &msg) noexcept;

    const char *what() const noexcept override;

    int line() const noexcept
    {
        return line_;
    }

    const std::string &file() const noexcept
    {
        return file_;
    }

private:
    int line_;
    std::string file_;
    std::string description_;
};

class InvalidArgumentException: public MyException {
public:
    InvalidArgumentException(int line,
                             const std::string &file,
                             const std::string &msg) noexcept
        : MyException(line, file, msg)
    {}
};

class ParseException: public MyException {
public:
    ParseException(int line,
                   const std::string &file,
                   const std::string &msg) noexcept
        : MyException(line, file, msg)
    {}
};

class FileException: public MyException {
public:
    FileException(int line,
                  const std::string &file,
                  const std::string &msg) noexcept
        : MyException(line, file, msg)
    {}
};

class OpenGLException: public MyException {
public:
    OpenGLException(int line,
                    const std::string &file,
                    const std::string &msg) noexcept
        : MyException(line, file, msg)
    {}
};

class MemoryException: public MyException {
public:
    MemoryException(int line,
                    const std::string &file,
                    const std::string &msg) noexcept
        : MyException(line, file, msg)
    {}
};

#define THROW_EXCEPT(ExceptionType, msg) \
    throw ExceptionType(__LINE__, __FILE__, msg);

} // end of namespace commonlib
} // end of namespace mcdane

#endif

