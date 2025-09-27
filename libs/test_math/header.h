
#include <math.h>
#include <string.h>


typedef struct vec2 {
	float x;
	float y;
} vec2;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;


static inline vec3 cross(const vec3 *const x, const vec3 *const y);

static inline float dot(const vec3 *const a, const vec3 *const b);

static inline vec3 foo(const vec3 *const a, const vec3 *const b);

static inline vec3 normalize(const vec3 v);

static inline void lookcatRH(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up);

static inline void fmat(float a[4], const float m[4]);

static inline void rotate(float matrix[4][4], const float angle, const vec3 *const v);

static inline void perspective(float matrix[4][4], const float fovy, const float aspect, const float zNear, const float zFar);


#include "header.inl"
