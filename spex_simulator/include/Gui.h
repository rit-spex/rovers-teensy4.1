#ifndef GUI_H
#define GUI_H

#include "Arduino.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

GLFWwindow *guiSetup();
void guiShutdown(GLFWwindow *window);

void pinStateWidget(PinState *pinStatePtr);

#endif // GUI_H
