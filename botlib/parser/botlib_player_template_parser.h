#ifndef INCLUDED_BOTLIB_PLAYER_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_PLAYER_TEMPLATE_PARSER_H

#include <botlib_robot_template_parser.h>

namespace mcdane {
namespace botlib {

class PlayerTemplate;

class PlayerTemplateParser: public RobotTemplateParser {
public:
    PlayerTemplateParser(const MissileTemplateLib& missileTemplateLib,
                         const ComponentTemplateLib& componentTemplateLib);

    void load(PlayerTemplate& t,
              const std::string& fileName);

};

} // end of namespace botlib
} // end of namespace mcdane

#endif

