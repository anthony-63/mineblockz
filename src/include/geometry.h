#ifndef MINEBLOCKZ_GEOMETRY_H
#define MINEBLOCKZ_GEOMETRY_H

// Basic geometry(these are not cubes yet!)
const float CUBE_VERTICES[] = {
    -0.5,  0.5, 0.0,
    -0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.5,  0.5, 0.0,
};

const int CUBE_INDICES[] = {
    0, 1, 2,
    0, 2, 3,
};

#endif