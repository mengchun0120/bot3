#ifndef INCLUDED_COMMONLIB_ARGUMENT_PARSER_H
#define INCLUDED_COMMONLIB_ARGUMENT_PARSER_H

#include <initializer_list>
#include <vector>
#include <unordered_map>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

class ArgumentParser {
public:
    ArgumentParser();

    ArgumentParser(std::initializer_list<Argument::Ptr> args);

    void init(const std::initializer_list<Argument::Ptr> &args);

    void parse(int argc, const char *const argv[]);

    bool argExists(const std::string &name) const
    {
        return nameArgMap_.find(name) != nameArgMap_.end();
    }

    bool shortOptExists(const std::string &shortOpt) const
    {
        return shortOptArgMap_.find(shortOpt) !=
               shortOptArgMap_.end();
    }

    bool longOptExists(const std::string &longOpt) const
    {
        return longOptArgMap_.find(longOpt) !=
               longOptArgMap_.end();
    }

private:
    void clearAll();

    void addArg(Argument::Ptr arg,
                unsigned int &posArgIdx);

    void addArgToNameArgMap(Argument::Ptr arg);

    void addArgToShortOptArgMap(Argument::Ptr arg);

    void addArgToLongOptArgMap(Argument::Ptr arg);

    void resetArgs();

    void evalArgs(int argc,
                  const char *const argv[]);

    void evalLongOpt(const std::string &longOpt,
                     int &argIdx,
                     int argc,
                     const char *const argv[]);

    void evalShortOpt(const std::string &shortOpt,
                      int &argIdx,
                      int argc,
                      const char *const argv[]);

    void evalPosOpt(unsigned int &posArgIdx,
                    int &argIdx,
                    const char *const argv[]);

    void checkNonOptional();

private:
    std::unordered_map<std::string, Argument::Ptr> nameArgMap_;
    std::vector<Argument::Ptr> posArgs_;
    std::unordered_map<std::string, Argument::Ptr> shortOptArgMap_;
    std::unordered_map<std::string, Argument::Ptr> longOptArgMap_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

