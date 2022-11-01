#include "include/shader.h"
#include "include/logging.h"

// Damn you windows with the weird backslashes!
#ifdef WIN32
#define PATH_SLASH "\\"
#else
#define PATH_SLASH "/"
#endif



GLuint load_shader(const char* src, GLenum type) {
    // Open a file and read it into a null-terminated string
    FILE* src_fp = fopen(src, "r");
    if (src_fp == NULL) {
        LOG_ERR("Failed to open file: %s", src);
    }
    fseek(src_fp, 0L, SEEK_END);
    size_t fsize = ftell(src_fp);
    rewind(src_fp);
    GLchar* src_buffer = malloc(fsize + 1);
    src_buffer[fsize] = '\0';
    if (src_buffer) {
        fread(src_buffer, 1, fsize, src_fp);
    }
    fclose(src_fp);

    // Create OpenGL shader and compile it
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, (const GLchar* const*)&src_buffer, NULL);
    glCompileShader(shader);

    // Error checking
    GLint compile_ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        GLint max_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_log_length);
        char* error_log = malloc(max_log_length * sizeof(char));
        glGetShaderInfoLog(shader, max_log_length, &max_log_length, &error_log[0]);
        glDeleteShader(shader);
        LOG_ERR("Failed to compile shader: %s\nLog:\n%s", src, error_log);
    }
    else {
        LOG_INFO("Loaded shader: %s", src);
    }
    free(src_buffer);
    return shader;
}

// Create all the shaders
MBShader* create_mb_shader(const char* vs_source, const char* fs_source) {
    char vs_buffer[512];
    snprintf(vs_buffer, 512, "assets%sshaders%s%s", PATH_SLASH, PATH_SLASH, vs_source);
    GLuint vshader = load_shader(vs_buffer, GL_VERTEX_SHADER);

    char fs_buffer[512];
    snprintf(fs_buffer, 512, "assets%sshaders%s%s", PATH_SLASH, PATH_SLASH, fs_source);
    GLuint fshader = load_shader(fs_buffer, GL_FRAGMENT_SHADER);

    MBShader* shader = malloc(sizeof * shader);

    shader->program = glCreateProgram();

    glAttachShader(shader->program, vshader);
    glAttachShader(shader->program, fshader);

    glLinkProgram(shader->program);

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return shader;
}

void use_mb_shader(MBShader* shader) {
    glUseProgram(shader->program);
}

int find_mb_shader_uniform(MBShader* shader, char* name) {
    return glGetUniformLocation(shader->program, name);
}

void load_mb_shader_uniform_matrix(MBShader* shader, char* name, mat4 matrix) {
    glUniformMatrix4fv(find_mb_shader_uniform(shader, name), 1, GL_FALSE, (float*)matrix);
}

void destroy_mb_shader(MBShader* shader) {
    glDeleteProgram(shader->program);
    free(shader);
}
