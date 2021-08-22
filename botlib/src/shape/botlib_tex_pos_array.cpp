#include <botlib_tex_pos_array.h>

namespace mcdane {
namespace botlib {

TexPosArray::TexPosArray(std::initializer_list<commonlib::Point2> texPos)
{
    load(texPos);
}

void TexPosArray::load(std::initializer_list<commonlib::Point2> texPos)
{
    load(texPos.begin(), texPos.end());
}

} // end of namespace botlib
} // end of namespace mcdane

