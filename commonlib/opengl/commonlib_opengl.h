#ifndef INCLUDED_COMMONLIB_OPENGL_H
#define INCLUDED_COMMONLIB_OPENGL_H

#if defined(_WIN32) || defined(__linux__)
#define DESKTOP_APP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#endif
