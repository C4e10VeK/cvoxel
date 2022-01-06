#ifndef CVOXEL_MACROS_H
#define CVOXEL_MACROS_H

#ifdef __unix
#define CVOX_INLINE inline __attribute((always_inline))
#elif defined(_WIN32)
#define CVOX_INLINE inline
#endif

#ifdef __unix
#define CVOX_STATIC_INLINE static inline __attribute((always_inline))
#elif defined(_WIN32)
#define CVOX_STATIC_INLINE static inline
#endif

#endif // CVOXEL_MACROS_H
