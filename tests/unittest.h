int passed = 0;
int failed = 0;

#define TEST(test_fn)       \
    do                      \
    {                       \
        if (test_fn() == 0) \
        {                   \
            passed++;       \
        }                   \
        else                \
        {                   \
            failed++;       \
        }                   \
    } while (0);
