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
                      Validator<T> validator=Validator<T>());

    static bool validateName(const std::string &name);

    static bool validateName(const char *name);

    static bool validateOpt(const std::string &opt);

    static bool validateOpt(const char *opt);

    Argument(const std::string &name,
             const std::string &shortOpt="",
             const std::string &longOpt="",
             const std::string &description="",
             bool optional=false);

    Argument(const Argument &other) noexcept = default;

    Argument(Argument&& other) noexcept = default;

    virtual ~Argument()
    {}

    Argument &operator=(const Argument& other) noexcept = default;

    Argument &operator=(Argument&& other) noexcept = default;

    inline const std::string &name() const noexcept;

    inline bool isPosArg() const noexcept;

    inline const std::string &shortOpt() const noexcept;

    inline const std::string &longOpt() const noexcept;

    inline const std::string &description() const noexcept;

    inline bool optional() const noexcept;

    inline bool specified() const noexcept;

    void setSpecified(bool v) noexcept;

    virtual void eval(const std::string &s) = 0;

protected:
    std::string name_;
    std::string shortOpt_;
    std::string longOpt_;
    std::string description_;
    bool optional_;
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
                  Validator<T> validator=Validator<T>());

    TypedArgument(const TypedArgument &other) noexcept = default;

    TypedArgument(TypedArgument&& other) noexcept = default;

    TypedArgument &operator=(const TypedArgument& other) noexcept = default;

    TypedArgument &operator=(TypedArgument&& other) noexcept = default;

    T &arg() noexcept
    {
        return arg_;
    }

    const T &arg() const noexcept
    {
        return arg_;
    }

    void eval(const std::string &s) override;

private:
    T &arg_;
    Validator<T> validator_;
};

template <typename T>
Argument::Ptr Argument::create(T &arg,
                               const std::string &name,
                               const std::string &shortOpt,
                               const std::string &longOpt,
                               const std::string &description,
                               bool optional,
                               Validator<T> validator)
{
    return Ptr(new TypedArgument<T>(arg, name, shortOpt,
                                    longOpt, description,
                                    optional, validator));
}

const std::string &Argument::name() const noexcept
{
    return name_;
}

bool Argument::isPosArg() const noexcept
{
    return shortOpt_.empty() && longOpt_.empty();
}

const std::string &Argument::shortOpt() const noexcept
{
    return shortOpt_;
}

const std::string &Argument::longOpt() const noexcept
{
    return longOpt_;
}

const std::string &Argument::description() const noexcept
{
    return description_;
}

bool Argument::optional() const noexcept
{
    return optional_;
}

bool Argument::specified() const noexcept
{
    return specified_;
}

template <typename T>
TypedArgument<T>::TypedArgument(T &arg,
                                const std::string &name,
                                const std::string &shortOpt,
                                const std::string &longOpt,
                                const std::string &description,
                                bool optional,
                                Validator<T> validator)
    : Argument(name, shortOpt, longOpt, description, optional)
    , arg_(arg)
    , validator_(validator)
{}

template <typename T>
void TypedArgument<T>::eval(const std::string &s)
{
    parse(arg_, s);
    if (!validator_.validate(arg_))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Validation failed: " + validator_.description(arg_));
    }
    specified_ = true;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

