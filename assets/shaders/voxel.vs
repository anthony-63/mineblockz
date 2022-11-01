#version 330

layout(location = 0) in vec3 position;

out vec3 position_pass;

uniform mat4 world_mat;
uniform mat4 p_mat;

void main(void) {
    position_pass = position;
    gl_Position = p_mat * world_mat * vec4(position, 1.0);
}