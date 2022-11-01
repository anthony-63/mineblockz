#include "include/window.h"
#include "include/logging.h"
#include "include/geometry.h"

// TEMPORARY
GLuint vao = 0;
GLuint vbo = 0;
GLuint ibo = 0;

const int INDICES_LENGTH = sizeof(CUBE_INDICES) / sizeof(CUBE_INDICES[0]);

void window_size_callback(GLFWwindow* raw_window, int width, int height) {
    LOG_INFO("Resized: %dx%d", width, height);
    glViewport(0, 0, width, height);
}

MBWindow* create_mbwindow(int width, int height, const char* title) {
    MBWindow* window = (MBWindow*)malloc(sizeof * window);
    LOG_INFO("Allocted window");

    if (!glfwInit()) {
        LOG_ERR("Failed to initialize GLFW!");
    }

    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->raw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    LOG_INFO("Created window");
    glfwSetWindowSizeCallback(window->raw_window, window_size_callback);
    glfwMakeContextCurrent(window->raw_window);
    LOG_INFO("Created OpenGL context");

    if (glewInit() != GLEW_OK) {
        LOG_ERR("Failed to get OpenGL context!");
    }

    LOG_INFO("Initialized GLEW");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), &CUBE_VERTICES[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), &CUBE_INDICES[0], GL_STATIC_DRAW);

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

void update(MBWindow* window) {

}

void draw(MBWindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, INDICES_LENGTH, GL_UNSIGNED_INT, NULL);
}

void run_mbwindow(MBWindow* window) {
    glClearColor(0.1, 0.2, 0.3, 1.0);
    while (!glfwWindowShouldClose(window->raw_window)) {
        glfwPollEvents();
        update(window);
        draw(window);
        glfwSwapBuffers(window->raw_window);
    }
}