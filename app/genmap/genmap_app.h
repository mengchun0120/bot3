#ifndef INCLUDED_GENMAP_APP_H
#define INCLUDED_GENMAP_APP_H

#include <commonlib_app.h>
#include <botlib_game_lib.h>

namespace mcdane {
namespace genmap {

class GenMapApp: public commonlib::App {
public:
    GenMapApp(const std::string& appConfigFile,
              const std::string& appDir,
              const std::string& algorithm,
              const std::string& algorithmConfigFile,
              const std::string& mapFile);

    ~GenMapApp() override;

    void run() override;

private:
    botlib::GameLib lib_;
};

} // end of namespace genmap
} // end of namespace mcdane

#endif
