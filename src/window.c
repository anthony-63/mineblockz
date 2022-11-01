#include "include/window.h"
#include "include/logging.h"

#include <GL/glew.h>

MBWindow* create_mbwindow(int width, int height, const char* title) {
    MBWindow* window = (MBWindow*)malloc(sizeof * window);
    LOG_INFO("Allocted window");

    if (!glfwInit()) {
        LOG_ERR("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->raw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    LOG_INFO("Created window");
    glfwMakeContextCurrent(window->raw_window);
    LOG_INFO("Created OpenGL context");

    if (glewInit() != GLEW_OK) {
        LOG_ERR("Failed to get OpenGL context!");
    }

    LOG_INFO("Initialized GLEW");

    return window;
}

void destroy_mbwindow(MBWindow* window) {
    LOG_INFO("Destroying window");
    glfwDestroyWindow(window->raw_window);
    LOG_INFO("Terminating GLFW");
    glfwTerminate();
    LOG_INFO("Freeing window");
    free(window);
}

void run_mbwindow(MBWindow* window) {
    while (!glfwWindowShouldClose(window->raw_window)) {
        glfwPollEvents();
        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window->raw_window);
    }
}