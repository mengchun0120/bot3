#ifndef INCLUDED_GENMAP_APP_H
#define INCLUDED_GENMAP_APP_H

#include <commonlib_app.h>

namespace mcdane {

namespace botlib {

class GameMap;
class GameMapGenerator;

} // end of namespace botlib

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
    void writeMap(const std::string& mapFile,
                  botlib::GameMap& map);

private:
    std::string mapFile_;
    botlib::GameMapGenerator* generator_;
};

} // end of namespace genmap
} // end of namespace mcdane

#endif
