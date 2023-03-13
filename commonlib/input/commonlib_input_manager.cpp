#include <commonlib_log.h>
#include <commonlib_input_manager.h>

namespace mcdane {
namespace commonlib {

std::shared_ptr<InputManager> InputManager::k_inputManager;

#ifdef DESKTOP_APP
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
    glfwSetCursorPosCallback(window_, handleMouseMove);
    glfwSetMouseButtonCallback(window_, handleMouseButton);
    glfwSetKeyCallback(window_, handleKey);
    enabled_ = true;
}

void InputManager::disable()
{
    if (!enabled_)
    {
        return;
    }

    glfwSetCursorPosCallback(window_, nullptr);
    glfwSetMouseButtonCallback(window_, nullptr);
    glfwSetKeyCallback(window_, nullptr);
    enabled_ = false;
}

void InputManager::clear()
{
    events_.clear();
}

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

#elif __ANDROID__

void InputManager::initInstance(android_app *app,
                                float width,
                                float height,
                                const Vector2 &viewportSize)
{
    if (k_inputManager)
    {
        LOG_WARN << "InputManger already initialized" << LOG_END;
        return;
    }

    k_inputManager.reset(
        new InputManager(app, width, height, viewportSize)
    );
}

InputManager::InputManager(android_app *app,
                             float width,
                             float height,
                             const Vector2 &viewportSize)
    : app_(app)
    , width_(width)
    , height_(height)
    , viewportSize_(viewportSize)
{
}

InputManager::~InputManager()
{
}

void InputManager::resetViewport(float width,
                                 float height,
                                 const Vector2 &viewportSize)
{
    width_ = width;
    height_ = height;
    viewportSize_ = viewportSize;
}

InputEvent InputManager::retrieveEvent(int i)
{
    InputEvent event;
    GameActivityMotionEvent &motionEvent = app_->motionEvents[i];
    int32_t action = motionEvent.action;

    event.index_ = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                   >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

    GameActivityPointerAxes &pointer = motionEvent.pointers[event.index_];
    event.x_ = GameActivityPointerAxes_getX(&pointer);
    event.y_ = GameActivityPointerAxes_getY(&pointer);

    switch(action & AINPUT_SOURCE_TOUCHSCREEN)
    {
        case AMOTION_EVENT_ACTION_DOWN:
        case AMOTION_EVENT_ACTION_POINTER_DOWN:
            event.type_ = InputEvent::POINTER_DOWN;
            break;

        case AMOTION_EVENT_ACTION_UP:
        case AMOTION_EVENT_ACTION_POINTER_UP:
            event.type_ = InputEvent::POINTER_UP;
            break;

        default:
            event.type_ = InputEvent::POINTER_MOVE;
    }

    return event;
}

#endif

} // end of namespace commonlib
} // end of namespace mcdane
