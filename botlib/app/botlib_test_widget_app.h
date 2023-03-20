#ifndef INCLUDED_BOTLIB_TEST_WIDGET_APP_H
#define INCLUDED_BOTLIB_TEST_WIDGET_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_message_box.h>

namespace mcdane {
namespace botlib {

class TestWidgetApp: public commonlib::App {
public:
    TestWidgetApp();

    TestWidgetApp(const std::string &configFile,
                  const std::string &appDir);

    ~TestWidgetApp() override = default;

#ifdef DESKTOP_APP
    void init(const std::string &configFile,
              const std::string &appDir);

#elif __ANDROID__
    void init(android_app *app,
              const std::string &configFile);

#endif

    void process() override;

    bool operator()(const commonlib::InputEvent &e);

private:
    void setupShader();

    void setupWidgets();

#ifdef DESKTOP_APP
    void setupInput();

#elif __ANDROID__
    void setupInput(android_app *app);

#endif

    void onViewportChange(float width, float height) override;

    void onStartGameClicked();

    void onSettingClicked();

    void onExitClicked();

private:
    botlib::WidgetGroup widgets_;
    botlib::MessageBox msgBox_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

