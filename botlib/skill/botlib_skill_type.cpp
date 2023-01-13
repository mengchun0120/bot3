#include <vector>
#include <commonlib_exception.h>
#include <botlib_skill_type.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

static const std::vector<std::string> k_skillTypeStr{
    "move",
    "shoot-missile",
};

const std::string& toString(SkillType type)
{
    return k_skillTypeStr[static_cast<int>(type)];
}

SkillType toSkillType(const std::string& typeStr)
{
    for (std::size_t i = 0; i < k_skillTypeStr.size(); ++i)
    {
        if (k_skillTypeStr[i] == typeStr)
        {
            return static_cast<SkillType>(i);
        }
    }

    THROW_EXCEPT(InvalidArgumentException, "Invalid skill type " + typeStr);
}

} // end of namespace botlib
} // end of namespace mcdane
