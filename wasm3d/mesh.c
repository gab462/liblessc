#include "mesh.h"
#include "math.h"

// Matrix multiplication
void rotate_mesh(struct mesh *mesh, float matrix[3][3])
{
	for (int vi = 0; vi < mesh->n_vertices; ++vi) {
		float *v = mesh->vertices[vi];
		float acc[3] = {0};

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				acc[i] += v[j] * matrix[i][j];

		for (int i = 0; i < 3; ++i)
			v[i] = acc[i];
	}
}

void rotate_mesh_x(struct mesh *mesh, float angle)
{
	float matrix[3][3] = {
		{ 1.0f, 0.0f,        0.0f },
		{ 0.0f, cos(angle), -sin(angle) },
		{ 0.0f, sin(angle),  cos(angle) }
	};

	rotate_mesh(mesh, matrix);
}

void rotate_mesh_y(struct mesh *mesh, float angle)
{
	float matrix[3][3] = {
		{  cos(angle), 0.0f, sin(angle) },
		{  0.0f,       1.0f, 0.0f },
		{ -sin(angle), 0.0f, cos(angle) }
	};

	rotate_mesh(mesh, matrix);
}

void rotate_mesh_z(struct mesh *mesh, float angle)
{
	float matrix[3][3] = {
		{ cos(angle), -sin(angle), 0.0f },
		{ sin(angle),  cos(angle), 0.0f },
		{ 0.0f,         0.0f,        1.0f }
	};

	rotate_mesh(mesh, matrix);
}

void zoom_mesh(struct mesh *mesh, float scale)
{
	for (int i = 0; i < mesh->n_vertices; ++i)
		for (int j = 0; j < 3; ++j)
			mesh->vertices[i][j] *= scale;
}

void offset_mesh(struct mesh *mesh, float offset[3])
{
	for (int i = 0; i < mesh->n_vertices; ++i)
		for (int j = 0; j < 3; ++j)
			mesh->vertices[i][j] += offset[j];
}
