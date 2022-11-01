#version 330

layout(location = 0) in vec3 position;

out vec3 position_pass;

void main(void) {
    position_pass = position;
    gl_Position = vec4(position, 1.0);
}