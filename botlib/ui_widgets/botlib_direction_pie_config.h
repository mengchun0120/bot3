#ifndef INCLUDED_BOTLIB_DIRECTION_PIE_CONFIG_H
#define INCLUDED_BOTLIB_DIRECTION_PIE_CONFIG_H

#include <string>
#include <commonlib_color.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class DirectionPieConfig {
public:
    DirectionPieConfig() = default;

    ~DirectionPieConfig() = default;

    void init(const std::string &fileName,
              const VertexArrayLib &vertexArrayLib);

    inline float radius() const;

    inline const commonlib::Color &color() const;

    inline float alpha() const;

    inline const commonlib::VertexArray *directionLine() const;

    inline const commonlib::VertexArray *directionCircle() const;;

private:
    float radius_;
    commonlib::Color color_;
    float alpha_;
    const commonlib::VertexArray *directionLine_;
    const commonlib::VertexArray *directionCircle_;
};

float DirectionPieConfig::radius() const
{
    return radius_;
}

const commonlib::Color &DirectionPieConfig::color() const
{
    return color_;
}

float DirectionPieConfig::alpha() const
{
    return alpha_;
}

const commonlib::VertexArray *DirectionPieConfig::directionLine() const
{
    return directionLine_;
}

const commonlib::VertexArray *DirectionPieConfig::directionCircle() const
{
    return directionCircle_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
