#ifndef INCLUDED_COMMONLIB_ALGORITHM_H
#define INCLUDED_COMMONLIB_ALGORITHM_H

namespace mcdane {
namespace commonlib {

template <typename Iterator>
unsigned int count(Iterator begin, Iterator end)
{
    unsigned int c = 0;
    for (Iterator it = begin; it != end; ++it)
    {
        ++c;
    }
    return c;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

