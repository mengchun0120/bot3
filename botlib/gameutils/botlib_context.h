#ifndef INCLUDED_BOTLIB_CONTEXT_H
#define INCLUDED_BOTLIB_CONTEXT_H

#include <botlib_app_config.h>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>

namespace mcdane {
namespace botlib {

class Context {
public:
    Context(const std::string& appCfgFileName,
            const std::string& appDir);

    inline const AppConfig& appCfg() const;

    inline Graphics& graphics();

    inline const GameLib& gameLib() const;

private:
    AppConfig appCfg_;
    Graphics graphics_;
    GameLib gameLib_;
};

const AppConfig& Context::appCfg() const
{
    return appCfg_;
}

Graphics& Context::graphics()
{
    return graphics_;
}

const GameLib& Context::gameLib() const
{
    return gameLib_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

