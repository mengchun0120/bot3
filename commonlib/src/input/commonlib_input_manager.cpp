#include <commonlib_log.h>
#include <commonlib_input_manager.h>

namespace mcdane {
namespace commonlib {

namespace {

bool validateInputManager(const std::string& func)
{
    InputManager& mgr = InputManager::getInstance();

    if (!mgr.enabled())
    {
        LOG_WARN << func << ": InputManager is disabled" << LOG_END;
        return false;
    }

    if (mgr.eventsFull())
    {
        LOG_WARN << "Input-event queue is full" << LOG_END;
        return false;
    }

    return true;
}

#ifdef DESKTOP_APP
void handleMouseButton(GLFWwindow* window,
                       int button,
                       int action,
                       int mods)
{
    if (!validateInputManager(__func__))
    {
        return;
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    InputManager::getInstance().addMouseButtonEvent(
        static_cast<float>(x), static_cast<float>(y), button, action, mods
    );
}

void handleMouseMove(GLFWwindow *window,
                     double x,
                     double y)
{
    if (!validateInputManager(__func__))
    {
        return;
    }

    InputManager::getInstance().addMouseMoveEvent(
        static_cast<float>(x), static_cast<float>(y)
    );
}

void handleKey(GLFWwindow* window,
               int key,
               int scancode,
               int action,
               int mods)
{
    if (!validateInputManager(__func__))
    {
        return;
    }

    InputManager::getInstance().addKeyEvent(key, scancode, action, mods);
}

} // end of unnamed namespace

std::shared_ptr<InputManager> InputManager::k_inputManager;

void InputManager::initInstance(GLFWwindow* window,
                                float viewportHeight,
                                unsigned int inputQueueCapacity)
{
    if (k_inputManager)
    {
        LOG_WARN << "InputManger already initialized" << LOG_END;
        return;
    }

    k_inputManager.reset(
        new InputManager(window, viewportHeight, inputQueueCapacity)
    );
}

InputManager::InputManager(GLFWwindow* window,
                           float viewportHeight,
                           unsigned int inputQueueCapacity)
{
    if (!window)
    {
        THROW_EXCEPT(InvalidArgumentException, "window is null");
    }

    if (viewportHeight <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "viewportHeight is invalid");
    }

    window_ = window;
    enabled_ = false;
    viewportHeight_ = viewportHeight;
    events_.init(inputQueueCapacity);
}
#endif

InputManager::~InputManager()
{
    disable();
}

void InputManager::enable()
{
    if (enabled_)
    {
        return;
    }

    clear();
#ifdef DESKTOP_APP
    glfwSetCursorPosCallback(window_, handleMouseMove);
    glfwSetMouseButtonCallback(window_, handleMouseButton);
    glfwSetKeyCallback(window_, handleKey);
#endif
    enabled_ = true;
}

void InputManager::disable()
{
    if (!enabled_)
    {
        return;
    }

#ifdef DESKTOP_APP
    glfwSetCursorPosCallback(window_, nullptr);
    glfwSetMouseButtonCallback(window_, nullptr);
    glfwSetKeyCallback(window_, nullptr);
#endif
    enabled_ = false;
}

void InputManager::clear()
{
    events_.clear();
}

void InputManager::processInput(InputProcessor& processor)
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

#ifdef DESKTOP_APP
bool InputManager::addMouseButtonEvent(float x,
                                       float y,
                                       int button,
                                       int action,
                                       int mods)
{
    InputEvent e;
    e.setMouseButtonEvent(x, viewportHeight_-y,
                          button, action, mods);
    return events_.enqueue(e);
}

bool InputManager::addMouseMoveEvent(float x,
                                     float y)
{
    InputEvent e;
    e.setMouseMoveEvent(x, viewportHeight_-y);
    return events_.enqueue(e);
}

bool InputManager::addKeyEvent(int key,
                               int scancode,
                               int action,
                               int mods)
{
    InputEvent e;
    e.setKeyEvent(key, action, scancode, mods);
    return events_.enqueue(e);
}
#endif

} // end of namespace commonlib
} // end of namespace mcdane

