

static inline vec3 cross(const vec3 *const x, const vec3 *const y)
{
	return (vec3) {
		(x->y * y->z) - (y->y * x->z),
		(x->z * y->x) - (y->z * x->x),
		(x->x * y->y) - (y->x * x->y)// прямиком из glm
	};
}

static inline float dot(const vec3 *const a, const vec3 *const b)
{
	vec3 tmp;
	tmp.x = a->x * b->x;
	tmp.y = a->y * b->y;
	tmp.z = a->z * b->z;
	return tmp.x + tmp.y + tmp.z;
}// адаптировано из glm: vec<3, T, Q> tmp(a * b);
// 			 return tmp.x + tmp.y + tmp.z;

static inline vec3 foo(const vec3 *const a, const vec3 *const b)
{
	return (vec3) {
		a->y - b->y,
		a->z - b->z,
		a->x - b->x
	};
}

static inline vec3 normalize(const vec3 v)
{
	const float w = (1.0 / sqrtf(dot(&v, &v)));
	if (w == 0)
	{
		return (vec3){0.0f, 0.0f, 0.0f};
	}
	else
	{
		return (vec3){
			v.x * w,
			v.y * w,
			v.z * w
		};
	}
}// адаптировано из glm, оригинал: return v * inversesqrt(dot(v, v));

// 23)))))

static inline void lookcatRH(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up)
{
		const vec3 forward = normalize(foo(cam_target, cam_pos));// same as normalize(cam_target - cam_pos);

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
		matrix[0][2] =-forward.x;
		matrix[1][2] =-forward.y;
		matrix[2][2] =-forward.z;
		matrix[3][0] =-dot(&right, cam_pos);
		matrix[3][1] =-dot(&up, cam_pos);
		matrix[3][2] = dot(&forward, cam_pos);
}


static inline void fmat(float a[4], const float m[4])
{
	a[0] = m[0];
	a[1] = m[1];
	a[2] = m[2];
	a[3] = m[3];
}


// T = float
static inline void rotate(float matrix[4][4], const float angle, const vec3 *const v)
{
	const float c = cosf(angle);
	const float s = sinf(angle);

	vec3 axis = normalize(*v);
	vec3 temp;
	temp.x = (1.0f - c) * axis.x;
	temp.y = (1.0f - c) * axis.y;
	temp.z = (1.0f - c) * axis.z;

	float Rotate[4][4];

// [0] = x
// [1] = y
// [2] = z
	Rotate[0][0] = c + temp.x * axis.x;
	Rotate[0][1] = temp.x * axis.y + s * axis.z;
	Rotate[0][2] = temp.x * axis.z - s * axis.y;

	Rotate[1][0] = temp.y * axis.x - s * axis.z;
	Rotate[1][1] = c + temp.y * axis.y;
	Rotate[1][2] = temp.y * axis.z + s * axis.x;

	Rotate[2][0] = temp.z * axis.x + s * axis.y;
	Rotate[2][1] = temp.z * axis.y - s * axis.x;
	Rotate[2][2] = c + temp.z * axis.z;

//	printf("Rotate:");
//	for (int i = 0; i < 4; i++)
//	{
//		printf("\n");
//		for (int j = 0; j < 4; j++)
//		{
//			printf(" | %f | ", Rotate[i][j]);
//		}
//	}
//	printf("end.\n");

	float m[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}};

	fmat(m[0], Rotate[0]);
	fmat(m[1], Rotate[1]);
	fmat(m[2], Rotate[2]);

	fmat(matrix[0], m[0]);
	fmat(matrix[1], m[1]);
	fmat(matrix[2], m[2]);
	fmat(matrix[3], m[3]);
}



static inline void perspective(float matrix[4][4], const float fovy, const float aspect, const float zNear, const float zFar)
{
	const float tanHalfFovy = tanf(fovy / 2.0f);

	matrix[0][0] = 1.0f / (aspect * tanHalfFovy);
	matrix[1][1] = 1.0f / (tanHalfFovy);
	matrix[2][2] = - (zFar + zNear) / (zFar - zNear);
	matrix[2][3] = - 1.0f;
	matrix[3][2] = - (2.0f * zFar * zNear) / (zFar - zNear);
}
