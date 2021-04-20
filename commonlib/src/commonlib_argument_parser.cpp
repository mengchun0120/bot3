#include <cstring>
#include <unordered_set>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

namespace {

unsigned int getNumPosArgs(const std::initializer_list<Argument::Ptr> &args)
{
    unsigned int count = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if ((*it)->IsPosArg())
        {
            ++count;
        }
    }

    return count;
}

bool checkLongOpt(std::string &long_opt, const char *arg)
{
    if (strlen(arg) < 3 || arg[0] != '-' || arg[1] != '-')
    {
        return false;
    }

    if (!Argument::ValidateOpt(arg + 2))
    {
        return false;
    }

    long_opt = arg + 2;

    return true;
}

bool checkShortOpt(std::string &short_opt, const char *arg)
{
    if (strlen(arg) < 2 || arg[0] != '-')
    {
        return false;
    }

    if (!Argument::ValidateOpt(arg + 1))
    {
        return false;
    }

    short_opt = arg + 1;

    return true;
}

} // end of unnamed namespace

ArgumentParser::ArgumentParser()
{
}

ArgumentParser::ArgumentParser(std::initializer_list<Argument::Ptr> args)
{
    initArgs(args);
}

void ArgumentParser::initArgs(const std::initializer_list<Argument::Ptr> &args)
{
    unsigned num_pos_args = getNumPosArgs(args);

    if (num_pos_args > 0)
    {
        pos_args_.resize(num_pos_args);
    }

    unsigned int pos_arg_idx = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        addArg(*it, pos_arg_idx);
    }
}

void ArgumentParser::addArg(Argument::Ptr arg, unsigned int &pos_arg_idx)
{
    addArgToNameArgMap(arg);

    if (arg->IsPosArg())
    {
        pos_args_[pos_arg_idx++] = arg;
        return;
    }

    if (!arg->ShortOpt().empty())
    {
        addArgToShortOptArgMap(arg);
    }

    if (!arg->LongOpt().empty())
    {
        addArgToLongOptArgMap(arg);
    }
}

void ArgumentParser::addArgToNameArgMap(Argument::Ptr arg)
{
    if (ArgExists(arg->Name()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate argument " + arg->Name());
    }

    name_arg_map_.insert({arg->Name(), arg});
}

void ArgumentParser::addArgToShortOptArgMap(Argument::Ptr arg)
{
    if (ShortOptExists(arg->ShortOpt()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate short option " + arg->ShortOpt());
    }

    short_opt_arg_map_.insert({arg->ShortOpt(), arg});
}

void ArgumentParser::addArgToLongOptArgMap(Argument::Ptr arg)
{
    if (LongOptExists(arg->LongOpt()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate long option " + arg->LongOpt());
    }

    long_opt_arg_map_.insert({arg->LongOpt(), arg});
}


void ArgumentParser::Parse(int argc, const char * const argv[])
{
    if (argc <= 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "argc must be greater than 1");
    }

    resetArgs();

    unsigned int pos_arg_idx = 0;
    int arg_idx = 1;

    while (arg_idx < argc)
    {
        std::string long_opt, short_opt;

        if (checkLongOpt(long_opt, argv[arg_idx]))
        {
            evalLongOpt(long_opt, arg_idx, argc, argv);
        }
        else if (checkShortOpt(short_opt, argv[arg_idx]))
        {
            evalShortOpt(short_opt, arg_idx, argc, argv);
        }
        else
        {
            evalPosOpt(pos_arg_idx, arg_idx, argv);
        }
    }
}

void ArgumentParser::resetArgs()
{
    for (auto it = name_arg_map_.begin(); it != name_arg_map_.end(); ++it)
    {
        it->second->Specified() = false;
    }
}

void ArgumentParser::evalLongOpt(const std::string &long_opt,
                                 int &arg_idx,
                                 int argc,
                                 const char * const argv[])
{
    auto it = long_opt_arg_map_.find(long_opt);
    if (it == long_opt_arg_map_.end())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unknown option " + long_opt);
    }

    if (arg_idx + 1 >= argc)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Not enough parameter for option " + long_opt);
    }

    it->second->Eval(argv[arg_idx+1]);
    arg_idx += 2;
}

void ArgumentParser::evalShortOpt(const std::string &short_opt,
                                  int &arg_idx,
                                  int argc,
                                  const char * const argv[])
{
    auto it = short_opt_arg_map_.find(short_opt);
    if (it == short_opt_arg_map_.end())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unknown option" + short_opt);
    }

    if (arg_idx + 1 >= argc)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Not enough parameter for option " + short_opt);
    }

    it->second->Eval(argv[arg_idx+1]);
    arg_idx += 2;
}

void ArgumentParser::evalPosOpt(unsigned int &pos_arg_idx,
                                int &arg_idx,
                                const char * const argv[])
{
    if (pos_arg_idx >= pos_args_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     std::string("Unknown option ") + argv[arg_idx]);
    }

    pos_args_[pos_arg_idx]->Eval(argv[arg_idx]);
    pos_arg_idx++;
    arg_idx++;
}

} // end of namespace commonlib
} // end of namespace mcdane

