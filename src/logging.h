#include <stdio.h>

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

#ifdef ENABLE_LOGGING
#define LOG(level, format, ...)                              \
    do                                                       \
    {                                                        \
        if (level == LOG_LEVEL_INFO)                         \
        {                                                    \
            printf("[INFO] " format "\n", ##__VA_ARGS__);    \
        }                                                    \
        else if (level == LOG_LEVEL_WARNING)                 \
        {                                                    \
            printf("[WARNING] " format "\n", ##__VA_ARGS__); \
        }                                                    \
        else if (level == LOG_LEVEL_ERROR)                   \
        {                                                    \
            printf("[ERROR] " format "\n", ##__VA_ARGS__);   \
        }                                                    \
    } while (0)
#else
#define LOG(level, format, ...)
#endif
