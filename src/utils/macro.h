#ifndef CVOX_INLINE
#define CVOX_INLINE inline __attribute((always_inline))
#endif

#ifndef CVOX_STATIC_INLINE
#define CVOX_STATIC_INLINE static inline __attribute((always_inline))
#endif

#ifndef START_SPEED_TEST
#define START_SPEED_TEST clock_t start = clock()
#endif

#ifndef STOP_SPEED_TEST
#define STOP_SPEED_TEST \
    clock_t end = clock();\
    double el = (double)(end - start) / CLOCKS_PER_SEC;\
    printf("Speed in %s: %f sec\n", __func__, el)
#endif
