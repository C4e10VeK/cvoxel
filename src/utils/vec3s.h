#ifndef CVOXEL_VEC3S_H
#define CVOXEL_VEC3S_H

#include "cglm/vec3.h"
#include <cglm/common.h>
#include <cglm/types-struct.h>

CGLM_INLINE vec3s vec3_add(vec3s a, vec3s b)
{
    vec3s res;
    glm_vec3_add(a.raw, b.raw, res.raw);
    return res;
}

CGLM_INLINE vec3s vec3_adds(vec3s a, float s)
{
    vec3s res;
    glm_vec3_adds(a.raw, s, res.raw);
    return res;
}

CGLM_INLINE vec3s vec3_sub(vec3s a, vec3s b)
{
    vec3s res;
    glm_vec3_sub(a.raw, b.raw, res.raw);
    return res;
}

CGLM_INLINE vec3s vec3_subs(vec3s a, float s)
{
    vec3s res;
    glm_vec3_subs(a.raw, s, res.raw);
    return res;
}

CGLM_INLINE vec3s vec3_multiply(vec3s a, vec3s b)
{
    vec3s res;
    glm_vec3_mul(a.raw, b.raw, res.raw);
    return res;
}

CGLM_INLINE vec3s vec3_normilize(vec3s vec)
{
    vec3s res = vec;
    glm_vec3_normalize(res.raw);
    return res;
}

#endif
