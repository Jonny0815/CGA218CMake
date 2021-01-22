#ifndef MESH_H
#define MESH_H

#include<vector>
#include<CommonTypes.h>
#include<ShaderProgram.h>
#include"Material.h"
using namespace std; 

class Mesh {
public:
	~Mesh();
	//Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index);
	Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index, Material mat);
	void render(ShaderProgram* shader);
	void setup();
	unsigned int VBO, VAO, IBO;

private:
	vector<Vertex> _vertecies;
	vector<VertexAttribute> _attributes;
	vector<Index> _indicies;
	Material _material;
	
};
#endif