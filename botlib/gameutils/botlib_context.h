#ifndef INCLUDED_BOTLIB_CONTEXT_H
#define INCLUDED_BOTLIB_CONTEXT_H

#include <memory>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>

namespace mcdane {
namespace botlib {

class AppConfig;

class Context {
public:
    static void init(const AppConfig& cfg);

    inline static Graphics& graphics();

    inline static const GameLib& gameLib();

    ~Context() = default;

private:
    Context(const AppConfig& cfg);

private:
    static std::shared_ptr<Context> k_context;

    Graphics graphics_;
    GameLib gameLib_;
};

Graphics& Context::graphics()
{
    return k_context->graphics_;
}

const GameLib& Context::gameLib()
{
    return k_context->gameLib_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

