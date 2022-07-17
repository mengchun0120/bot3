#ifndef INCLUDED_BOTLIB_AI_LIB_H
#define INCLUDED_BOTLIB_AI_LIB_H

#include <commonlib_named_map.h>
#include <botlib_chase_shoot_ai_param.h>

namespace mcdane {
namespace botlib {

class AILib {
public:
    AILib() = default;

    void init(const std::string& chaseShootAIParamFile);

    inline const ChaseShootAIParam* findChaseShootAIParam(
                                        const std::string& name) const;

private:
    void initChaseShootAIParamLib(const std::string& chaseShootAIParamFile);

private:
    commonlib::NamedMap<ChaseShootAIParam> chaseShootAIParamLib_;
};

const ChaseShootAIParam* AILib::findChaseShootAIParam(
                                        const std::string& name) const
{
    return chaseShootAIParamLib_.search(name);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

