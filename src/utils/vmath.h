#ifndef CVOXEL_VMATH_H
#define CVOXEL_VMATH_H

#define PI 3.14159265358979323846

#define CVOX_RADIANS(deg) ((__typeof__(deg))((deg * PI) / 180))
#define CVOX_DEGRES(rad) ((__typeof__(rad))((rad * 180) / PI))

#define CVOX_MIN(v1, v2) ( v1 < v2 ? v1 : v2 )
#define CVOX_MAX(v1, v2) ( v1 > v2 ? v1 : v2 )

#define CVOX_CLAMP(v, mn, mx) ({ __typeof__(v) t = v < mn ? mn : v;\
							t > mx ? mx : t; })

#endif // CVOXEL_VMATH_H