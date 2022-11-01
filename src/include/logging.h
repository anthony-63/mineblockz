#ifndef MB_LOGGING_H
#define MB_LOGGING_H
#include <stdio.h>
#include <stdlib.h>

enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
};

#ifdef WIN32
// No ascii color codes windows cmd prompt :(
#define __LOG_WITH_LEVEL(level, ...) \
    printf("[MINEBLOCKZ] "); printf(__VA_ARGS__); printf("\n")
#else
// Colors!
#define __LOG_WITH_LEVEL(level, ...) \
    switch(level) { \
        case LOG_LEVEL_INFO: printf("\x1b[90m"); break; \
        case LOG_LEVEL_WARNING: printf("\x1b[33m"); break; \
        case LOG_LEVEL_ERROR: {\
            fprintf(stderr, "\x1b[91m[MINEBLOCKZ] "); \
            fprintf(stderr, __VA_ARGS__); \
            fprintf(stderr, "\x1b[0m\n"); \
            exit(-1); \
        }\
    } \
    printf("[MINEBLOCKZ] "); printf(__VA_ARGS__); printf("\x1B[0m\n")
#endif


#define LOG_INFO(...) __LOG_WITH_LEVEL(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...) __LOG_WITH_LEVEL(LOG_LEVEL_WARNING, __VA_ARGS__)
#define LOG_ERR(...) __LOG_WITH_LEVEL(LOG_LEVEL_ERROR, __VA_ARGS__)

#endif