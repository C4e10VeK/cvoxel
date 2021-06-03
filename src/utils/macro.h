#ifndef CVOX_INLINE
#define CVOX_INLINE inline __attribute((always_inline))
#ifdef _WIN32
#define CVOX_INLINE inline
#endif
#endif // CVOX_INLINE

#ifndef CVOX_STATIC_INLINE
#define CVOX_STATIC_INLINE static inline __attribute((always_inline))
#ifdef _WIN32
#define CVOX_STATIC_INLINE static inline
#endif
#endif // CVOX_STATIC_INLINE

#ifndef START_SPEED_TEST
#define START_SPEED_TEST clock_t start = clock()
#endif // START_SPEED_TEST

#ifndef STOP_SPEED_TEST
#define STOP_SPEED_TEST \
    clock_t end = clock();\
    double el = (double)(end - start) / CLOCKS_PER_SEC;\
    printf("Speed in %s: %f sec\n", __func__, el)
#endif // STOP_SPEED_TEST
