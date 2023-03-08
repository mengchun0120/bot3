#ifndef INCLUDED_COMMONLIB_OPENGL_H
#define INCLUDED_COMMONLIB_OPENGL_H

#ifdef DESKTOP_APP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#endif

#endif
