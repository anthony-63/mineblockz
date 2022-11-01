#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"

typedef struct MBWindow {
    GLFWwindow* raw_window;
} MBWindow;

MBWindow* create_mbwindow(int width, int height, const char* title);
void destroy_mbwindow(MBWindow* window);
void run_mbwindow(MBWindow* window);