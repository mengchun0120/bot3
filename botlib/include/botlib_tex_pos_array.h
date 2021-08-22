#ifndef INCLUDED_BOTLIB_TEX_POS_ARRAY_H
#define INCLUDED_BOTLIB_TEX_POS_ARRAY_H

#include <vector>
#include <initializer_list>
#include <commonlib_vector.h>
#include <commonlib_algorithm.h>
#include <commonlib_exception.h>
#include <commonlib_opengl_utils.h>

namespace mcdane {
namespace botlib {

class TexPosArray {
public:
    TexPosArray() = default;

    TexPosArray(std::initializer_list<commonlib::Point2> texPos);

    template <typename Iterator>
    TexPosArray(Iterator begin, Iterator end);

    virtual ~TexPosArray() = default;

    void load(std::initializer_list<commonlib::Point2> texPos);

    template <typename Iterator>
    void load(Iterator begin, Iterator end);

    unsigned int numVertices() const
    {
        return texPos_.size();
    }

    const commonlib::Point2* texPos() const
    {
        return texPos_.data();
    }

protected:
    std::vector<commonlib::Point2> texPos_;
};

template <typename Iterator>
TexPosArray::TexPosArray(Iterator begin, Iterator end)
{
    load(begin, end);
}

template <typename Iterator>
void TexPosArray::load(Iterator begin, Iterator end)
{
    unsigned num = count(begin, end);
    if (num == 0)
    {
        THROW_EXCEPT(commonlib::InvalidArgumentException,
                     "No vertices specified");
    }

    texPos_.resize(num);

    unsigned int i = 0;
    for (auto it = begin; it != end; ++it, ++i)
    {
        validateTexPos(*it);
        texPos_[i] = *it;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

