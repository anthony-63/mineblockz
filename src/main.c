#include <stdio.h>
#include <stdlib.h>
#include "include/window.h"

const int WIDTH = 1280, HEIGHT = 720;
const char* TITLE = "Mineblockz | v0.1 - ALPHA";

int main() {
    MBWindow* window = create_mbwindow(WIDTH, HEIGHT, TITLE);
    run_mbwindow(window);
    destroy_mbwindow(window);
}