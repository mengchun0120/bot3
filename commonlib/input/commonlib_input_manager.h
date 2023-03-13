#ifndef INCLUDED_COMMONLIB_INPUT_MANAGER_H
#define INCLUDED_COMMONLIB_INPUT_MANAGER_H

#include <memory>
#include <functional>

#ifdef __ANDROID__
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include <commonlib_fixed_queue.h>
#include <commonlib_input_event.h>
#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

class InputManager {
public:
    inline static InputManager & instance();

#ifdef DESKTOP_APP
    static void initInstance(GLFWwindow *window,
                             float viewportHeight,
                             unsigned int inputQueueCapacity);

    InputManager(GLFWwindow *window,
                 float viewportHeight,
                 unsigned int inputQueueCapacity);

    inline bool eventsFull() const;

    bool addMouseButtonEvent(float x,
                             float y,
                             int button,
                             int action,
                             int mods);

    bool addMouseMoveEvent(float x,
                           float y);

    bool addKeyEvent(int key,
                     int scancode,
                     int action,
                     int mods);

    void clear();

    inline bool enabled() const;

    void enable();

    void disable();

#elif __ANDROID__
    static void initInstance(android_app *app,
                             float width,
                             float height,
                             const Vector2 &viewportSize);

    InputManager(android_app *app,
                 float width,
                 float height,
                 const Vector2 &viewportSize);

    void resetViewport(float width,
                       float height,
                       const Vector2 &viewportSize);

    InputEvent retrieveEvent(int i);
#endif

    ~InputManager();

    template <typename P>
    void processInput(P &processor);

private:
    static std::shared_ptr<InputManager> k_instance;

#ifdef DESKTOP_APP
    GLFWwindow *window_;
    FixedQueue<InputEvent> events_;
    bool enabled_;
    float viewportHeight_;

#elif __ANDROID__
    android_app *app_;
    float width_;
    float height_;
    Vector2 viewportSize_;
#endif

};

InputManager & InputManager::instance()
{
    return *k_instance;
}

#ifdef DESKTOP_APP
bool InputManager::enabled() const
{
    return enabled_;
}

bool InputManager::eventsFull() const
{
    return events_.full();
}

template <typename P>
void InputManager::processInput(P &processor)
{
    while (!events_.empty())
    {
        InputEvent e;
        events_.dequeue(e);
        if (!processor(e))
        {
            break;
        }
    }
}

#elif __ANDROID__

template <typename P>
void InputManager::processInput(P &processor)
{
    for (auto i = 0; i < app_->motionEventsCount; i++)
    {
        InputEvent event = retrieveEvent(i);
        if (!processor(event))
        {
            break;
        }
    }

    android_app_clear_motion_events(app_);
}

#endif

} // end of namespace commonlib
} // end of namespace mcdane

#endif

