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
        if ((*it)->isPosArg())
        {
            ++count;
        }
    }

    return count;
}

bool checkLongOpt(std::string &longOpt, const char *arg)
{
    if (strlen(arg) < 3 || arg[0] != '-' || arg[1] != '-')
    {
        return false;
    }

    if (!Argument::validateOpt(arg + 2))
    {
        return false;
    }

    longOpt = arg + 2;

    return true;
}

bool checkShortOpt(std::string &shortOpt, const char *arg)
{
    if (strlen(arg) < 2 || arg[0] != '-')
    {
        return false;
    }

    if (!Argument::validateOpt(arg + 1))
    {
        return false;
    }

    shortOpt = arg + 1;

    return true;
}

} // end of unnamed namespace

ArgumentParser::ArgumentParser()
{
}

ArgumentParser::ArgumentParser(std::initializer_list<Argument::Ptr> args)
{
    init(args);
}

void ArgumentParser::init(const std::initializer_list<Argument::Ptr> &args)
{
    clearAll();

    unsigned numPosArgs = getNumPosArgs(args);

    if (numPosArgs > 0)
    {
        posArgs_.resize(numPosArgs);
    }

    unsigned int posArgIdx = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        addArg(*it, posArgIdx);
    }
}

void ArgumentParser::clearAll()
{
    nameArgMap_.clear();
    posArgs_.clear();
    shortOptArgMap_.clear();
    longOptArgMap_.clear();
}

void ArgumentParser::addArg(Argument::Ptr arg, unsigned int &posArgIdx)
{
    addArgToNameArgMap(arg);

    if (arg->isPosArg())
    {
        posArgs_[posArgIdx++] = arg;
        return;
    }

    if (!arg->shortOpt().empty())
    {
        addArgToShortOptArgMap(arg);
    }

    if (!arg->longOpt().empty())
    {
        addArgToLongOptArgMap(arg);
    }
}

void ArgumentParser::addArgToNameArgMap(Argument::Ptr arg)
{
    if (argExists(arg->name()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate argument " + arg->name());
    }

    nameArgMap_.insert({arg->name(), arg});
}

void ArgumentParser::addArgToShortOptArgMap(Argument::Ptr arg)
{
    if (shortOptExists(arg->shortOpt()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate short option " + arg->shortOpt());
    }

    shortOptArgMap_.insert({arg->shortOpt(), arg});
}

void ArgumentParser::addArgToLongOptArgMap(Argument::Ptr arg)
{
    if (longOptExists(arg->longOpt()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Duplicate long option " + arg->longOpt());
    }

    longOptArgMap_.insert({arg->longOpt(), arg});
}


void ArgumentParser::parse(int argc, const char * const argv[])
{
    if (argc <= 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "argc must be greater than 1");
    }

    resetArgs();
    evalArgs(argc, argv);
    checkNonOptional();
}

void ArgumentParser::resetArgs()
{
    for (auto it = nameArgMap_.begin(); it != nameArgMap_.end(); ++it)
    {
        it->second->specified() = false;
    }
}

void ArgumentParser::evalArgs(int argc,
                              const char * const argv[])
{
    unsigned int posArgIdx = 0;
    int argIdx = 1;

    while (argIdx < argc)
    {
        std::string longOpt, shortOpt;

        if (checkLongOpt(longOpt, argv[argIdx]))
        {
            evalLongOpt(longOpt, argIdx, argc, argv);
        }
        else if (checkShortOpt(shortOpt, argv[argIdx]))
        {
            evalShortOpt(shortOpt, argIdx, argc, argv);
        }
        else
        {
            evalPosOpt(posArgIdx, argIdx, argv);
        }
    }
}

void ArgumentParser::evalLongOpt(const std::string &longOpt,
                                 int &argIdx,
                                 int argc,
                                 const char * const argv[])
{
    auto it = longOptArgMap_.find(longOpt);
    if (it == longOptArgMap_.end())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unknown option --" + longOpt);
    }

    Argument::Ptr &arg = it->second;

    if (arg->specified())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Parameter " + arg->name() + " was already specified");
    }

    if (argIdx + 1 >= argc)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "No value specified for parameter " + arg->name());
    }

    arg->eval(argv[argIdx+1]);
    argIdx += 2;
}

void ArgumentParser::evalShortOpt(const std::string &shortOpt,
                                  int &argIdx,
                                  int argc,
                                  const char * const argv[])
{
    auto it = shortOptArgMap_.find(shortOpt);
    if (it == shortOptArgMap_.end())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unknown option -" + shortOpt);
    }

    Argument::Ptr &arg = it->second;

    if (arg->specified())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Parameter " + arg->name() + " was already specified");
    }

    if (argIdx + 1 >= argc)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "No value specified for parameter " + arg->name());
    }

    arg->eval(argv[argIdx+1]);
    argIdx += 2;
}

void ArgumentParser::evalPosOpt(unsigned int &posArgIdx,
                                int &argIdx,
                                const char * const argv[])
{
    if (posArgIdx >= posArgs_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     std::string("Unknown option ") + argv[argIdx]);
    }

    posArgs_[posArgIdx]->eval(argv[argIdx]);
    posArgIdx++;
    argIdx++;
}

void ArgumentParser::checkNonOptional()
{
    for (auto it = nameArgMap_.begin(); it != nameArgMap_.end(); ++it)
    {
        Argument::Ptr &arg = it->second;
        if (!arg->optional() && !arg->specified())
        {
            THROW_EXCEPT(InvalidArgumentException,
                         "Non-optional argument " + it->first + " not specifed");
        }
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

