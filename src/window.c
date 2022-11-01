#include "include/window.h"
#include "include/logging.h"
#include "include/geometry.h"
#include "include/cglm/struct.h"
#include "include/cglm/affine.h"

float last = 0.0;

// TEMPORARY
GLuint vao = 0;
GLuint vbo = 0;
GLuint ibo = 0;

float x = 0;

// ALSO TEMPORARY
const int INDICES_LENGTH = sizeof(CUBE_INDICES) / sizeof(CUBE_INDICES[0]);

// Resize the viewport when the window is resized
void window_size_callback(GLFWwindow* raw_window, int width, int height) {
    LOG_INFO("Resized: %dx%d", width, height);
    glViewport(0, 0, width, height);
}

MBWindow* create_mb_window(int width, int height, const char* title) {
    MBWindow* window = malloc(sizeof * window);
    LOG_INFO("Allocted window");

    window->width = width;
    window->height = height;

    if (!glfwInit()) {
        LOG_ERR("Failed to initialize GLFW!");
    }

    // Set the openl profile to core and version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->raw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    LOG_INFO("Created window");
    // Make sure the resize callback is set
    glfwSetWindowSizeCallback(window->raw_window, window_size_callback);

    glfwMakeContextCurrent(window->raw_window);
    LOG_INFO("Created OpenGL context");

    if (glewInit() != GLEW_OK) {
        LOG_ERR("Failed to get OpenGL context!");
    }

    LOG_INFO("Initialized GLEW");

    // All this should be self explanatory
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

    // create voxel shader(find them in assets/shaders/voxel.*)
    window->voxel_shader = create_mb_shader("voxel.vs", "voxel.fs");
    use_mb_shader(window->voxel_shader);
    window->dt = 0;

    return window;
}

void destroy_mb_window(MBWindow* window) {
    LOG_INFO("Destroying voxel shader");
    destroy_mb_shader(window->voxel_shader);

    LOG_INFO("Destroying window");
    glfwDestroyWindow(window->raw_window);

    LOG_INFO("Freeing window");
    free(window);

    LOG_INFO("Terminating GLFW");
    glfwTerminate();
}

void update(MBWindow* window) {
    window->dt = glfwGetTime() - last;
    last = glfwGetTime();
    x += window->dt;

    mat4 world_matrix = GLM_MAT4_IDENTITY_INIT;
    mat4 p_matrix = GLM_MAT4_IDENTITY_INIT;
    glm_perspective(glm_rad(90.0), (double)window->width / (double)window->height, 0.1, 500.0, p_matrix);
    glm_rotate(world_matrix, sin(x / 3.0 * 2.0) / 2.0, (vec3) { 0.0, 1.0, 0.0 });
    glm_rotate(world_matrix, x, (vec3) { 1.0, 0.0, 0.0 });
    glm_translate(world_matrix, (vec3) { 0.0, 0.0, 1.0 });

    load_mb_shader_uniform_matrix(window->voxel_shader, "world_mat", world_matrix);
    load_mb_shader_uniform_matrix(window->voxel_shader, "p_mat", p_matrix);
}

void draw(MBWindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, INDICES_LENGTH, GL_UNSIGNED_INT, NULL);
}

void run_mb_window(MBWindow* window) {
    glClearColor(0.1, 0.2, 0.3, 1.0);
    while (!glfwWindowShouldClose(window->raw_window)) {
        glfwPollEvents();
        update(window);
        draw(window);
        glfwSwapBuffers(window->raw_window);
    }
}