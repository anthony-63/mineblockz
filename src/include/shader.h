#ifndef MINEBLOCKZ_SHADER_H
#define MINEBLOCKZ_SHADER_H

#include "cglm/mat4.h"

#include "gfx.h"

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

typedef struct {
    GLuint program;
} MBShader;

// Allocate a MBShader*
MBShader* create_mb_shader(const char* vs_source, const char* fs_source);
void destroy_mb_shader(MBShader* shader);

void use_mb_shader(MBShader* shader);

void load_mb_shader_uniform_matrix(MBShader* shader, char* name, mat4 matrix);

#endif