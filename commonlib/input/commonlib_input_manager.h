#ifndef INCLUDED_COMMONLIB_INPUT_MANAGER_H
#define INCLUDED_COMMONLIB_INPUT_MANAGER_H

#include <memory>
#include <functional>
#include <commonlib_fixed_queue.h>
#include <commonlib_input_event.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP
using InputProcessor = std::function<bool(const InputEvent&)>;
#endif

class InputManager {
public:
    inline static InputManager& getInstance();

#ifdef DESKTOP_APP
    static void initInstance(GLFWwindow* window,
                             float viewportHeight,
                             unsigned int inputQueueCapacity);
#endif

    ~InputManager();

    inline bool enabled() const;

    void enable();

    void disable();

    void clear();

#ifdef DESTKOP_APP
    inline bool eventsFull() const;


    void processInput(InputProcessor& processor);

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
#endif

private:
#ifdef DESKTOP_APP
    InputManager(GLFWwindow* window,
                 float viewportHeight,
                 unsigned int inputQueueCapacity);
#endif

private:
    static std::shared_ptr<InputManager> k_inputManager;

#ifdef DESKTOP_APP
    GLFWwindow* window_;
    FixedQueue<InputEvent> events_;
#endif
    bool enabled_;
    float viewportHeight_;
};

InputManager& InputManager::getInstance()
{
    return *k_inputManager;
}

bool InputManager::enabled() const
{
    return enabled_;
}

#ifdef DESKTOP_APP
bool InputManager::eventsFull() const
{
    return events_.full();
}
#endif

} // end of namespace commonlib
} // end of namespace mcdane

#endif

