#ifndef INCLUDED_BOTLIB_LABEL_CONFIG_H
#define INCLUDED_BOTLIB_LABEL_CONFIG_H

#include <string>
#include <commonlib_color.h>

namespace mcdane {
namespace botlib {

class LabelConfig {
public:
    LabelConfig() = default;

    ~LabelConfig() = default;

    void init(const std::string configFile);

    inline const commonlib::Color &defaultTextColor() const;

    inline const commonlib::Color &defaultBackColor() const;

    inline const commonlib::Color &defaultBorderColor() const;

private:
    commonlib::Color defaultTextColor_;
    commonlib::Color defaultBackColor_;
    commonlib::Color defaultBorderColor_;
};

const commonlib::Color &LabelConfig::defaultTextColor() const
{
    return defaultTextColor_;
}

const commonlib::Color &LabelConfig::defaultBackColor() const
{
    return defaultBackColor_;
}

const commonlib::Color &LabelConfig::defaultBorderColor() const
{
    return defaultBorderColor_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

