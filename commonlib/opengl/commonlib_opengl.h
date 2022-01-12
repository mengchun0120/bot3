#ifndef include_sharedlib_opengl_h
#define include_sharedlib_opengl_h

#if defined(_WIN32) || defined(__linux__)
#define DESKTOP_APP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#endif
