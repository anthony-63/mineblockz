#include "gfx.h"
#include "shader.h"

typedef struct {
    GLFWwindow* raw_window;
    MBShader* voxel_shader;
} MBWindow;

// Allocate a window
MBWindow* create_mb_window(int width, int height, const char* title);
// Cleanup memory
void destroy_mb_window(MBWindow* window);
// Run the loop of polling, updating, and drawing
void run_mb_window(MBWindow* window);