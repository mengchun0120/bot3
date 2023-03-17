#ifndef INCLUDED_BOTLIB_MOVE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_MOVE_SKILL_TEMPLATE_H

#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class MoveSkillTemplate: public SkillTemplate {
public:
    MoveSkillTemplate();

    MoveSkillTemplate(const rapidjson::Value &v);

    void init(const rapidjson::Value &v);

    inline bool hasDest() const;

    inline float speed() const;

protected:
    bool hasDest_;
    float speed_;
};

bool MoveSkillTemplate::hasDest() const
{
    return hasDest_;
}

float MoveSkillTemplate::speed() const
{
    return speed_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
