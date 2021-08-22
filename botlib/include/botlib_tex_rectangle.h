#ifndef INCLUDED_BOTLIB_TEX_RECTANGLE_H
#define INCLUDED_BOTLIB_TEX_RECTANGLE_H

#include <botlib_tex_pos_array.h>

namespace mcdane {
namespace botlib {

class TexRectangle: public TexPosArray {
public:
    TexRectangle(float width=1.0f,
                 float height=1.0f,
                 float centerX=0.5f,
                 float centerY=0.5f);

    ~TexRectangle() override = default;

    float width() const
    {
        return width_;
    }

    float height() const
    {
        return height_;
    }

private:
    float width_, height_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

