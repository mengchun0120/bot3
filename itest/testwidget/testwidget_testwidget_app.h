#ifndef INCLUDED_TESTWIDGET_TESTWIDGET_APP_H
#define INCLUDED_TESTWIDGET_TESTWIDGET_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_widget_group.h>

namespace mcdane {
namespace testwidget {

class TestWidgetApp: public commonlib::App {
public:
    TestWidgetApp(const std::string& configFile,
                  const std::string& appDir);

    ~TestWidgetApp() override = default;

    void preProcess() override;

    void process() override;

    void postProcess() override;

    bool processInput(const commonlib::InputEvent& e);

private:
    void setupOpenGL();

    void setupWidgets();

    void setupInput();

private:
    botlib::AppConfig cfg_;
    botlib::WidgetGroup widgets_;
    commonlib::InputProcessor inputProcessor_;
};

} // end of namespace testwidget
} // end of namespace mcdane

#endif

