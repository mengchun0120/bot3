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
#include <botlib_game_screen_config.h>
#include <botlib_goodie_generator.h>

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

    inline static const GameScreenConfig& gameScreenConfig();

    inline static GoodieGenerator& goodieGenerator();

private:
    static Graphics k_graphics;
    static GameLib k_gameLib;
    static HPIndicatorConfig k_hpIndicatorConfig;
    static ButtonConfig k_buttonConfig;
    static LabelConfig k_labelConfig;
    static MessageBoxConfig k_msgBoxConfig;
    static StartScreenConfig k_startScreenConfig;
    static GameScreenConfig k_gameScreenConfig;
    static GoodieGenerator k_goodieGenerator;
};

Graphics& Context::graphics()
{
    return k_graphics;
}

const GameLib& Context::gameLib()
{
    return k_gameLib;
}

const HPIndicatorConfig& Context::hpIndicatorConfig()
{
    return k_hpIndicatorConfig;
}

const ButtonConfig& Context::buttonConfig()
{
    return k_buttonConfig;
}

const LabelConfig& Context::labelConfig()
{
    return k_labelConfig;
}

const MessageBoxConfig& Context::msgBoxConfig()
{
    return k_msgBoxConfig;
}

const StartScreenConfig& Context::startScreenConfig()
{
    return k_startScreenConfig;
}

const GameScreenConfig& Context::gameScreenConfig()
{
    return k_gameScreenConfig;
}

GoodieGenerator& Context::goodieGenerator()
{
    return k_goodieGenerator;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

