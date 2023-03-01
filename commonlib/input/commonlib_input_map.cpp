#include <commonlib_opengl.h>
#include <commonlib_input_map.h>

namespace mcdane {
namespace commonlib {

InputMap::InputMap()
{
    init();
}

int InputMap::get(const std::string& name) const
{
    auto it = map_.find(name);
    return it != map_.end() ? it->second : -1;
}

void InputMap::init()
{
#ifdef DESKTOP_APP
    map_ = {
        {"right-mouse", GLFW_MOUSE_BUTTON_RIGHT},
        {"0",           GLFW_KEY_0},
        {"1",           GLFW_KEY_1},
        {"2",           GLFW_KEY_2},
        {"3",           GLFW_KEY_3},
        {"4",           GLFW_KEY_4},
        {"5",           GLFW_KEY_5},
        {"6",           GLFW_KEY_6},
        {"7",           GLFW_KEY_7},
        {"8",           GLFW_KEY_8},
        {"9",           GLFW_KEY_9},
        {"A",           GLFW_KEY_A},
        {"B",           GLFW_KEY_B},
        {"C",           GLFW_KEY_C},
        {"D",           GLFW_KEY_D},
        {"E",           GLFW_KEY_E},
        {"F",           GLFW_KEY_F},
        {"G",           GLFW_KEY_G},
        {"H",           GLFW_KEY_H},
        {"I",           GLFW_KEY_I},
        {"J",           GLFW_KEY_J},
        {"K",           GLFW_KEY_K},
        {"L",           GLFW_KEY_L},
        {"M",           GLFW_KEY_M},
        {"N",           GLFW_KEY_N},
        {"O",           GLFW_KEY_O},
        {"P",           GLFW_KEY_P},
        {"Q",           GLFW_KEY_Q},
        {"R",           GLFW_KEY_R},
        {"S",           GLFW_KEY_S},
        {"T",           GLFW_KEY_T},
        {"U",           GLFW_KEY_U},
        {"V",           GLFW_KEY_V},
        {"W",           GLFW_KEY_W},
        {"X",           GLFW_KEY_X},
        {"Y",           GLFW_KEY_Y},
        {"Z",           GLFW_KEY_Z},
    };
#endif
}

} // end of namespace commonlib
} // end of namespace mcdane
