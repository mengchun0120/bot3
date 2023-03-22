#ifndef INCLUDED_BOTLIB_CONTEXT_H
#define INCLUDED_BOTLIB_CONTEXT_H

#include <memory>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>
#include <botlib_hp_indicator_config.h>
#include <botlib_button_config.h>
#include <botlib_label_config.h>
#include <botlib_message_box_config.h>
#include <botlib_map_navigator_config.h>
#include <botlib_game_navigator_config.h>
#include <botlib_start_screen_config.h>
#include <botlib_game_screen_config.h>
#include <botlib_show_map_screen_config.h>
#include <botlib_game_config.h>
#include <botlib_goodie_generator.h>

namespace mcdane {
namespace botlib {

class AppConfig;

class Context {
public:
    static void init(const AppConfig &cfg);

    inline static Graphics &graphics();

    inline static const GameLib &gameLib();

    inline static const HPIndicatorConfig &hpIndicatorConfig();

    inline static const ButtonConfig &buttonConfig();

    inline static const LabelConfig &labelConfig();

    inline static const MessageBoxConfig &msgBoxConfig();

    inline static const MapNavigatorConfig &mapNavigatorConfig();

    inline static const GameNavigatorConfig &gameNavigatorConfig();

    inline static const StartScreenConfig &startScreenConfig();

    inline static GameScreenConfig &gameScreenConfig();

    inline static ShowMapScreenConfig &showMapScreenConfig();

    inline static const GameConfig &gameConfig();

    inline static GoodieGenerator &goodieGenerator();

private:
    Context(const AppConfig &cfg);

private:
    static std::shared_ptr<Context> k_instance;
    Graphics graphics_;
    GameLib gameLib_;
    HPIndicatorConfig hpIndicatorConfig_;
    ButtonConfig buttonConfig_;
    LabelConfig labelConfig_;
    MessageBoxConfig msgBoxConfig_;
    MapNavigatorConfig mapNavigatorConfig_;
    GameNavigatorConfig gameNavigatorConfig_;
    StartScreenConfig startScreenConfig_;
    GameScreenConfig gameScreenConfig_;
    ShowMapScreenConfig showMapScreenConfig_;
    GameConfig gameConfig_;
    GoodieGenerator goodieGenerator_;
};

Graphics &Context::graphics()
{
    return k_instance->graphics_;
}

const GameLib &Context::gameLib()
{
    return k_instance->gameLib_;
}

const HPIndicatorConfig &Context::hpIndicatorConfig()
{
    return k_instance->hpIndicatorConfig_;
}

const ButtonConfig &Context::buttonConfig()
{
    return k_instance->buttonConfig_;
}

const LabelConfig &Context::labelConfig()
{
    return k_instance->labelConfig_;
}

const MessageBoxConfig &Context::msgBoxConfig()
{
    return k_instance->msgBoxConfig_;
}

const MapNavigatorConfig &Context::mapNavigatorConfig()
{
    return k_instance->mapNavigatorConfig_;
}

const GameNavigatorConfig &Context::gameNavigatorConfig()
{
    return k_instance->gameNavigatorConfig_;
}

const StartScreenConfig &Context::startScreenConfig()
{
    return k_instance->startScreenConfig_;
}

GameScreenConfig &Context::gameScreenConfig()
{
    return k_instance->gameScreenConfig_;
}

ShowMapScreenConfig &Context::showMapScreenConfig()
{
    return k_instance->showMapScreenConfig_;
}

const GameConfig &Context::gameConfig()
{
    return k_instance->gameConfig_;
}

GoodieGenerator &Context::goodieGenerator()
{
    return k_instance->goodieGenerator_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

