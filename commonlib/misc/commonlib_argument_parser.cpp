#include <cstring>
#include <unordered_set>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

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

void ArgumentParser::parse(int argc, const char *const argv[])
{
    if (argc <= 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "argc must be greater than 1");
    }

    std::vector<std::string> args(argc);
    for (int i = 0; i < argc; ++i)
    {
        args[i] = argv[i];
    }

    parse(args);
}

void ArgumentParser::parse(const std::vector<std::string> &args)
{
    resetArgs();
    evalArgs(args);
    checkNonOptional();
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

void ArgumentParser::resetArgs()
{
    for (auto it = nameArgMap_.begin(); it != nameArgMap_.end(); ++it)
    {
        it->second->setSpecified(false);
    }
}

void ArgumentParser::evalArgs(const std::vector<std::string> &args)
{
    unsigned int posArgIdx = 0;
    int argIdx = 0;

    while (argIdx < static_cast<int>(args.size()))
    {
        std::string longOpt, shortOpt;

        if (checkLongOpt(longOpt, args[argIdx]))
        {
            evalLongOpt(longOpt, argIdx, args);
        }
        else if (checkShortOpt(shortOpt, args[argIdx]))
        {
            evalShortOpt(shortOpt, argIdx, args);
        }
        else
        {
            evalPosOpt(posArgIdx, argIdx, args);
        }
    }
}

void ArgumentParser::evalLongOpt(const std::string &longOpt,
                                 int &argIdx,
                                 const std::vector<std::string> &args)
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

    if (argIdx + 1 >= static_cast<int>(args.size()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "No value specified for parameter " + arg->name());
    }

    arg->eval(args[argIdx+1]);
    argIdx += 2;
}

void ArgumentParser::evalShortOpt(const std::string &shortOpt,
                                  int &argIdx,
                                  const std::vector<std::string> &args)
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

    if (argIdx + 1 >= static_cast<int>(args.size()))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "No value specified for parameter " + arg->name());
    }

    arg->eval(args[argIdx+1]);
    argIdx += 2;
}

void ArgumentParser::evalPosOpt(unsigned int &posArgIdx,
                                int &argIdx,
                                const std::vector<std::string> &args)
{
    if (posArgIdx >= posArgs_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unknown option " + args[argIdx]);
    }

    posArgs_[posArgIdx]->eval(args[argIdx]);
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

unsigned int ArgumentParser::getNumPosArgs(
                        const std::initializer_list<Argument::Ptr> &args)
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

bool ArgumentParser::checkLongOpt(std::string &longOpt,
                                  const std::string &arg)
{
    if (arg.size() < 3 || arg[0] != '-' || arg[1] != '-')
    {
        return false;
    }

    std::string opt = arg.substr(2);
    if (!Argument::validateOpt(opt))
    {
        return false;
    }

    longOpt = opt;

    return true;
}

bool ArgumentParser::checkShortOpt(std::string &shortOpt,
                                   const std::string &arg)
{
    if (arg.size() < 2 || arg[0] != '-')
    {
        return false;
    }

    std::string opt = arg.substr(1);
    if (!Argument::validateOpt(opt))
    {
        return false;
    }

    shortOpt = opt;

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane
