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
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const CompositeObjectTemplate* getTemplate() const;

    inline float directionX() const;

    inline float directionY() const;

    inline const commonlib::Vector2& direction() const;

    inline unsigned int numComponents() const;

    inline const Component& component(unsigned int idx) const;

    inline const std::vector<Component>& components() const;

    void present() const override;

    void shiftPos(const commonlib::Vector2& delta) override;

    virtual void setDirection(const commonlib::Vector2& direction1);

    std::string toString() const override;

private:
    void initComponents();

    void repositionComponents();

    void shiftComponents(const commonlib::Vector2& delta);

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

unsigned int CompositeObject::numComponents() const
{
    return getTemplate()->numComponents();
}

const std::vector<Component>& CompositeObject::components() const
{
    return components_;
}

const Component& CompositeObject::component(unsigned int idx) const
{
    return components_[idx];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

