#ifndef CVOXEL_MACROS_H
#define CVOXEL_MACROS_H

#if defined(__clang__) || defined(__GNUC__)
#define CVOX_INLINE inline __attribute__((always_inline))
#elif defined(_WIN32)
#define CVOX_INLINE inline
#endif

#if defined(__clang__) || defined(__GNUC__)
#define CVOX_STATIC_INLINE static inline __attribute__((always_inline))
#elif defined(_WIN32)
#define CVOX_STATIC_INLINE static inline
#endif

#define UNUSED(s) ((void)s)

#endif // CVOXEL_MACROS_H
