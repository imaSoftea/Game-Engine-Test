#ifndef WINDOW

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* CreateWindow();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
