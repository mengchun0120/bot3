#ifndef INCLUDED_COMMONLIB_ARGUMENT_H
#define INCLUDED_COMMONLIB_ARGUMENT_H

#include <string>
#include <memory>
#include <commonlib_parse.h>
#include <commonlib_validator.h>

namespace mcdane {
namespace commonlib {

class Argument {
public:
    using Ptr = std::shared_ptr<Argument>;

public:
    template <typename T>
    static Ptr create(T &arg,
                      const std::string &name,
                      const std::string &shortOpt="",
                      const std::string &longOpt="",
                      const std::string &description="",
                      bool optional=false,
                      Validator validator=Validator());

    static bool validateName(const std::string &name);

    static bool validateName(const char *name);

    static bool validateOpt(const std::string &opt);

    static bool validateOpt(const char *opt);

    Argument(const std::string &name,
             const std::string &shortOpt="",
             const std::string &longOpt="",
             const std::string &description="",
             bool optional=false,
             Validator validator=Validator());

    Argument(const Argument &other) noexcept = default;

    Argument(Argument &&other) noexcept = default;

    virtual ~Argument()
    {}

    Argument &operator=(const Argument &other) noexcept = default;

    Argument &operator=(Argument &&other) noexcept = default;

    const std::string &name() const noexcept
    {
        return name_;
    }

    bool isPosArg() const noexcept
    {
        return shortOpt_.empty() && longOpt_.empty();
    }

    const std::string &shortOpt() const noexcept
    {
        return shortOpt_;
    }

    const std::string &longOpt() const noexcept
    {
        return longOpt_;
    }

    const std::string &description() const noexcept
    {
        return description_;
    }

    bool optional() const noexcept
    {
        return optional_;
    }

    const Validator &validator() const noexcept
    {
        return validator_;
    }

    virtual void eval(const char *s) = 0;

    bool &specified() noexcept
    {
        return specified_;
    }

    bool specified() const noexcept
    {
        return specified_;
    }

private:
    std::string name_;
    std::string shortOpt_;
    std::string longOpt_;
    std::string description_;
    bool optional_;
    Validator validator_;
    bool specified_;
};

template <typename T>
class TypedArgument: public Argument {
public:
    TypedArgument(T &arg,
                  const std::string &name,
                  const std::string &shortOpt="",
                  const std::string &longOpt="",
                  const std::string &description="",
                  bool optional=false,
                  Validator validator=Validator());

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

    void eval(const char *s) override;

private:
    T &arg_;
};

template <typename T>
Argument::Ptr Argument::create(T &arg,
                               const std::string &name,
                               const std::string &shortOpt,
                               const std::string &longOpt,
                               const std::string &description,
                               bool optional,
                               Validator validator)
{
    return Ptr(new TypedArgument<T>(arg, name, shortOpt,
                                    longOpt, description,
                                    optional, validator));
}

template <typename T>
TypedArgument<T>::TypedArgument(T &arg,
                                const std::string &name,
                                const std::string &shortOpt,
                                const std::string &longOpt,
                                const std::string &description,
                                bool optional,
                                Validator validator):
    Argument(name, shortOpt, longOpt, description, optional, validator),
    arg_(arg)
{}

template <typename T>
void TypedArgument<T>::eval(const char *s)
{
    parse(arg_, s);
    if (!validator().validate())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Validation failed: " + validator().description());
    }
    specified() = true;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

