struct mesh {
	int n_vertices;
	int n_edges;
	float (*vertices)[3];
	int (*edges)[2];
};

void rotate_mesh(struct mesh *mesh, float matrix[3][3]);

void rotate_mesh_x(struct mesh *mesh, float angle);

void rotate_mesh_y(struct mesh *mesh, float angle);

void rotate_mesh_z(struct mesh *mesh, float angle);

void zoom_mesh(struct mesh *mesh, float scale);

void offset_mesh(struct mesh *mesh, float offset[3]);
