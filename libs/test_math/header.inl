
static inline float radians(const float x)
{
	return x * PI / 180;
}

static inline vec3 cross(const vec3 *const a, const vec3 *const b)
{
	return (vec3) {
		(a->y * b->z) - (b->y * a->z),
		(a->z * b->x) - (b->z * a->x),
		(a->x * b->y) - (b->x * a->y)
	};
}

static inline float dot(const vec3 *const a, const vec3 *const b)
{
	vec3 tmp;
	tmp.x = a->x * b->x;
	tmp.y = a->y * b->y;
	tmp.z = a->z * b->z;
	return tmp.x + tmp.y + tmp.z;
}

static inline vec3 foo(const vec3 *const a, const vec3 *const b)
{
	return (vec3) {
		a->x - b->x,
		a->y - b->y,
		a->z - b->z
	};
}

static inline vec3 normalize(const vec3 v)
{
	const float w = (1.0 / sqrtf(dot(&v, &v)));
	return (vec3){
		v.x * w,
		v.y * w,
		v.z * w
	};
}

// lookAt_RH
static inline void lookAt(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up)
{
		const vec3 forward = normalize(foo(cam_target, cam_pos));
		const vec3 right = normalize(cross(&forward, cam_up));
		const vec3 up = cross(&right, &forward);

//		matrix[0][0] = 1;
//		matrix[1][1] = 1;
//		matrix[2][2] = 1;
		matrix[3][3] = 1;

		matrix[0][0] = right.x;
		matrix[1][0] = right.y;
		matrix[2][0] = right.z;
		matrix[0][1] = up.x;
		matrix[1][1] = up.y;
		matrix[2][1] = up.z;
		matrix[0][2] = -forward.x;
		matrix[1][2] = -forward.y;
		matrix[2][2] = -forward.z;
		matrix[3][0] = -dot(&right, cam_pos);
		matrix[3][1] = -dot(&up, cam_pos);
		matrix[3][2] = dot(&forward, cam_pos);
}

static inline void rotate(float matrix[4][4], const float angle, const vec3 *const v)
{
	const float c = cosf(radians(angle));
	const float s = sinf(radians(angle));

	const vec3 axis = normalize(*v);
	const vec3 temp = {
		(1.0f - c) * axis.x,
		(1.0f - c) * axis.y,
		(1.0f - c) * axis.z
	};

	float Rotate[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}};

	Rotate[0][0] = c + temp.x * axis.x;
	Rotate[0][1] = temp.x * axis.y + s * axis.z;
	Rotate[0][2] = temp.x * axis.z - s * axis.y;

	Rotate[1][0] = temp.y * axis.x - s * axis.z;
	Rotate[1][1] = c + temp.y * axis.y;
	Rotate[1][2] = temp.y * axis.z + s * axis.x;

	Rotate[2][0] = temp.z * axis.x + s * axis.y;
	Rotate[2][1] = temp.z * axis.y - s * axis.x;
	Rotate[2][2] = c + temp.z * axis.z;

	matrix[0][0] = Rotate[0][0];
	matrix[0][1] = Rotate[0][1];
	matrix[0][2] = Rotate[0][2];
	matrix[0][3] = Rotate[0][3];

	matrix[1][0] = Rotate[1][0];
	matrix[1][1] = Rotate[1][1];
	matrix[1][2] = Rotate[1][2];
	matrix[1][3] = Rotate[1][3];

	matrix[2][0] = Rotate[2][0];
	matrix[2][1] = Rotate[2][1];
	matrix[2][2] = Rotate[2][2];
	matrix[2][3] = Rotate[2][3];

	matrix[3][0] = Rotate[3][0];
	matrix[3][1] = Rotate[3][1];
	matrix[3][2] = Rotate[3][2];
	matrix[3][3] = Rotate[3][3];
}

static inline void perspective(float matrix[4][4], const float fov, const float aspect, const float zNear, const float zFar)
{
	const float x = 1.0f / tanf(radians(fov) / 2.0f);
	const float range = (zFar - zNear);

	matrix[0][0] = x / aspect;
	matrix[1][1] = x;
	matrix[2][2] = -(zFar + zNear) / range;
	matrix[2][3] = -1.0f;
	matrix[3][2] = -(2.0f * zFar * zNear) / range;

//	matrix[0][0] = 1.0f / (aspect * tanHalfFovy);
//	matrix[1][1] = 1.0f / (tanHalfFovy);
//	matrix[2][2] = - (zFar + zNear) / (zFar - zNear);
//	matrix[2][3] = -1.0f;
//	matrix[3][2] = - (2.0f * zFar * zNear) / (zFar - zNear);
}
