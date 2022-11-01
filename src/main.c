#include <stdio.h>
#include <stdlib.h>
#include "include/window.h"

const int WIDTH = 1280, HEIGHT = 720;
const char* TITLE = "Mineblockz | v0.1 - ALPHA";

int main() {
    MBWindow* window = create_mb_window(WIDTH, HEIGHT, TITLE);
    run_mb_window(window);
    destroy_mb_window(window);
}