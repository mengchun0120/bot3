#include <vector>
#include <commonlib_exception.h>
#include <botlib_text_size.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::vector<std::string> k_textSizeStr{
    "big",
    "medium",
    "small",
    "tiny"
};

TextSize toTextSize(const std::string &s)
{
    unsigned int k;
    for (k = 0; k < k_textSizeStr.size(); ++k)
    {
        if (s == k_textSizeStr[k])
        {
            break;
        }
    }

    if (k == k_textSizeStr.size())
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid text-size" + s);
    }

    return static_cast<TextSize>(k);
}

bool isValidTextSizeStr(const std::string &s)
{
    unsigned int k;
    for (k = 0; k < k_textSizeStr.size(); ++k)
    {
        if (s == k_textSizeStr[k])
        {
            return true;
        }
    }

    return false;
}

} // end of namespace botlib
} // end of namespace mcdane

