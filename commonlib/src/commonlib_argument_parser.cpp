#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

namespace {

} // end of unnamed namespace

ArgumentParser::ArgumentParser()
{
}

ArgumentParser::ArgumentParser(std::initializer_list<Argument::Ptr> args):
    args_(args)
{
}

void ArgumentParser::Parse(int argc, const char * const argv[])
{
    if (argc <= 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "argc must be greater than 1");
    }
/*
    auto it = args_.cbegin();

    for (int i = 1; i < argc && it != args_.cend(); ++i)
    {
        if (it->short_opt() == "" && it->long_opt() == "")
        {
            
        }
    }
    */
}

} // end of namespace commonlib
} // end of namespace mcdane
