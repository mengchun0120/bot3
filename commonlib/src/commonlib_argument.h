#ifndef INCLUDED_COMMONLIB_ARGUMENT_H
#define INCLUDED_COMMONLIB_ARGUMENT_H

#include <string>
#include <memory>
#include <commonlib_parse.h>

namespace mcdane {
namespace commonlib {

class Argument {
public:
    using Ptr = std::shared_ptr<Argument>;

public:
    template <typename T>
    static Ptr Create(T &arg,
                      const std::string &name,
                      const std::string &short_opt="",
                      const std::string &long_opt="",
                      const std::string &description="");

    static bool ValidateName(const std::string &name);

    static bool ValidateName(const char *name);

    static bool ValidateOpt(const std::string &opt);

    static bool ValidateOpt(const char *opt);

    explicit Argument(const std::string &name,
                      const std::string &short_opt="",
                      const std::string &long_opt="",
                      const std::string &description="");

    Argument(const Argument &other) noexcept = default;

    Argument(Argument &&other) noexcept = default;

    virtual ~Argument()
    {}

    Argument &operator=(const Argument &other) noexcept = default;

    Argument &operator=(Argument &&other) noexcept = default;

    const std::string &Name() const noexcept
    {
        return name_;
    }

    bool IsPosArg() const noexcept
    {
        return short_opt_.empty() && long_opt_.empty();
    }

    const std::string &ShortOpt() const noexcept
    {
        return short_opt_;
    }

    const std::string &LongOpt() const noexcept
    {
        return long_opt_;
    }

    const std::string &Description() const noexcept
    {
        return description_;
    }

    virtual void Eval(const char *s)
    {
    }

    bool &Specified() noexcept
    {
        return specified_;
    }

    bool Specified() const noexcept
    {
        return specified_;
    }

private:
    std::string name_;
    std::string short_opt_;
    std::string long_opt_;
    std::string description_;
    bool specified_;
};

template <typename T>
class TypedArgument: public Argument {
public:
    TypedArgument(T &arg,
                  const std::string &name,
                  const std::string &short_opt="",
                  const std::string &long_opt="",
                  const std::string &description="");

    TypedArgument(const TypedArgument &other) noexcept = default;

    TypedArgument(TypedArgument &&other) noexcept = default;

    TypedArgument &operator=(const TypedArgument &other) noexcept = default;

    TypedArgument &operator=(TypedArgument &&other) noexcept = default;

    T &arg() noexcept
    {
        return arg_;
    }

    const T &arg() const noexcept
    {
        return arg_;
    }

    void Eval(const char *s) override;

private:
    T &arg_;
};

template <typename T>
Argument::Ptr Argument::Create(T &arg,
                               const std::string &name,
                               const std::string &short_opt,
                               const std::string &long_opt,
                               const std::string &description)
{
    return Ptr(new TypedArgument<T>(arg, name, short_opt,
                                    long_opt, description));
}

template <typename T>
TypedArgument<T>::TypedArgument(T &arg,
                                const std::string &name,
                                const std::string &short_opt,
                                const std::string &long_opt,
                                const std::string &description):
    Argument(name, short_opt, long_opt, description),
    arg_(arg)
{}

template <typename T>
void TypedArgument<T>::Eval(const char *s)
{
    Parse(arg_, s);
    Specified() = true;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

