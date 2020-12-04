#ifndef MESH_H
#define MESH_H

#include<vector>
#include<CommonTypes.h>
#include<ShaderProgram.h>
using namespace std; 

class Mesh {
public:
	~Mesh();
	Mesh();
	Mesh(vector<Vertex>, vector<VertexAttribute>, vector<Index>);
	void render();
	void setup();
	unsigned int VBO, VAO, IBO;

private:
	vector<Vertex> _vertecies;
	vector<VertexAttribute> _attributes;
	vector<Index> _indicies;
};
#endif