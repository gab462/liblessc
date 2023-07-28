#include "mesh.h"
#include "math.h"

void rotate(float point[3], float matrix[3][3])
{
	float acc[3] = {0};

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			acc[i] += point[j] * matrix[i][j];

	for (int i = 0; i < 3; ++i)
		point[i] = acc[i];
}

void rotate_point(float point[3], float angle, enum axis axis)
{
	switch (axis) {
	case AXIS_X:
		rotate(point, (float[3][3]){
			{ 1.0f, 0.0f,        0.0f       },
			{ 0.0f, cos(angle), -sin(angle) },
			{ 0.0f, sin(angle),  cos(angle) }
		});
		break;
	case AXIS_Y:
		rotate(point, (float[3][3]){
			{  cos(angle), 0.0f, sin(angle) },
			{  0.0f,       1.0f, 0.0f       },
			{ -sin(angle), 0.0f, cos(angle) }
		});
		break;
	case AXIS_Z:
		rotate(point, (float[3][3]){
			{ cos(angle), -sin(angle), 0.0f },
			{ sin(angle),  cos(angle), 0.0f },
			{ 0.0f,         0.0f,      1.0f }
		});
		break;
	};
}

// Matrix multiplication
void rotate_mesh(struct mesh *mesh, float angle, enum axis axis)
{
	for (int vi = 0; vi < mesh->n_vertices; ++vi) {
		float *v = mesh->vertices[vi];

		rotate_point(v, angle, axis);
	}
}
