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

    void Parse(int argc, const char * const argv[]);

    bool ArgExists(const std::string &name) const
    {
        return name_arg_map_.find(name) != name_arg_map_.end();
    }

    bool ShortOptExists(const std::string &short_opt) const
    {
        return short_opt_arg_map_.find(short_opt) !=
               short_opt_arg_map_.end();
    }

    bool LongOptExists(const std::string &long_opt) const
    {
        return long_opt_arg_map_.find(long_opt) !=
               long_opt_arg_map_.end();
    }

private:
    void initArgs(const std::initializer_list<Argument::Ptr> &args);

    void resetArgs();

    void addArg(Argument::Ptr arg,
                unsigned int &pos_arg_idx);

    void addArgToNameArgMap(Argument::Ptr arg);

    void addArgToShortOptArgMap(Argument::Ptr arg);

    void addArgToLongOptArgMap(Argument::Ptr arg);

    void evalLongOpt(const std::string &long_opt,
                     int &arg_idx,
                     int argc,
                     const char * const argv[]);

    void evalShortOpt(const std::string &short_opt,
                      int &arg_idx,
                      int argc,
                      const char * const argv[]);

    void evalPosOpt(unsigned int &pos_arg_idx,
                    int &arg_idx,
                    const char * const argv[]);

private:
    std::unordered_map<std::string, Argument::Ptr> name_arg_map_;
    std::vector<Argument::Ptr> pos_args_;
    std::unordered_map<std::string, Argument::Ptr> short_opt_arg_map_;
    std::unordered_map<std::string, Argument::Ptr> long_opt_arg_map_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

