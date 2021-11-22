#ifndef INCLUDED_BOTLIB_COMPOSITE_OBJECT_H
#define INCLUDED_BOTLIB_COMPOSITE_OBJECT_H

#include <botlib_game_object.h>
#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class CompositeObject: public GameObject {
public:
    CompositeObject();

    ~CompositeObject() override = default;

    void init(const CompositeObjectTemplate* t,
              float x,
              float y,
              float directionX,
              float directionY);

    void init(const CompositeObjectTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const CompositeObjectTemplate* getTemplate() const;

    inline float directionX() const;

    inline float directionY() const;

    inline const commonlib::Vector2& direction() const;

    inline const Component& component(unsigned int idx) const;

    void present() const override;

    void setPos(float x,
                float y) override;

    void shiftPos(float deltaX,
                  float deltaY) override;

    void setDirection(float directionX,
                      float directionY);

private:
    void initComponents();

    void repositionComponents();

    void shiftComponents(float deltaX,
                         float deltaY);

protected:
    commonlib::Vector2 direction_;
    std::vector<Component> components_;
};

const CompositeObjectTemplate* CompositeObject::getTemplate() const
{
    return static_cast<const CompositeObjectTemplate*>(t_);
}

float CompositeObject::directionX() const
{
    return direction_[0];
}

float CompositeObject::directionY() const
{
    return direction_[1];
}

const commonlib::Vector2& CompositeObject::direction() const
{
    return direction_;
}

const Component& CompositeObject::component(unsigned int idx) const
{
    return components_[idx];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

