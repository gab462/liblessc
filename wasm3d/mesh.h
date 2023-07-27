struct mesh {
	int n_vertices;
	int n_edges;
	float (*vertices)[3];
	int (*edges)[2];
};

enum axis {
	AXIS_X,
	AXIS_Y,
	AXIS_Z
};

void rotate_point(float point[3], float angle, enum axis axis);

void rotate_mesh(struct mesh *mesh, float angle, enum axis axis);
