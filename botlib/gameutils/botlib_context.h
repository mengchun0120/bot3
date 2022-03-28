#ifndef INCLUDED_BOTLIB_CONTEXT_H
#define INCLUDED_BOTLIB_CONTEXT_H

#include <memory>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>
#include <botlib_hp_indicator_config.h>
#include <botlib_button_config.h>
#include <botlib_label_config.h>
#include <botlib_message_box_config.h>
#include <botlib_start_screen_config.h>

namespace mcdane {
namespace botlib {

class AppConfig;

class Context {
public:
    static void init(const AppConfig& cfg);

    inline static Graphics& graphics();

    inline static const GameLib& gameLib();

    inline static const HPIndicatorConfig& hpIndicatorConfig();

    inline static const ButtonConfig& buttonConfig();

    inline static const LabelConfig& labelConfig();

    inline static const MessageBoxConfig& msgBoxConfig();

    inline static const StartScreenConfig& startScreenConfig();

    ~Context() = default;

private:
    Context(const AppConfig& cfg);

private:
    static std::shared_ptr<Context> k_context;

    Graphics graphics_;
    GameLib gameLib_;
    HPIndicatorConfig hpIndicatorConfig_;
    ButtonConfig buttonConfig_;
    LabelConfig labelConfig_;
    MessageBoxConfig msgBoxConfig_;
    StartScreenConfig startScreenConfig_;
};

Graphics& Context::graphics()
{
    return k_context->graphics_;
}

const GameLib& Context::gameLib()
{
    return k_context->gameLib_;
}

const HPIndicatorConfig& Context::hpIndicatorConfig()
{
    return k_context->hpIndicatorConfig_;
}

const ButtonConfig& Context::buttonConfig()
{
    return k_context->buttonConfig_;
}

const LabelConfig& Context::labelConfig()
{
    return k_context->labelConfig_;
}

const MessageBoxConfig& Context::msgBoxConfig()
{
    return k_context->msgBoxConfig_;
}

const StartScreenConfig& Context::startScreenConfig()
{
    return k_context->startScreenConfig_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

