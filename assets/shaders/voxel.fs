#version 330

out vec4 color;

in vec3 position_pass;

void main(void) {
    color = vec4(position_pass / 2.0 + 0.5, 1.0);
}