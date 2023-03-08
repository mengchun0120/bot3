#ifndef INCLUDED_ITEST_TESTWIDGET_APP_H
#define INCLUDED_ITEST_TESTWIDGET_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_message_box.h>

namespace mcdane {
namespace itest {

class TestWidgetApp: public commonlib::App {
public:
    TestWidgetApp(const std::string& configFile,
                  const std::string& appDir);

    ~TestWidgetApp() override = default;

    void process() override;

    bool processInput(const commonlib::InputEvent& e);

private:
    void setupShader();

    void setupWidgets();

    void setupInput();

    void onStartGameClicked();

    void onSettingClicked();

    void onExitClicked();

private:
    botlib::WidgetGroup widgets_;
    botlib::MessageBox msgBox_;
    commonlib::InputProcessor inputProcessor_;
    commonlib::Color fillColor_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif
