#ifndef MESH_H
#define MESH_H

#include<vector>
#include<CommonTypes.h>
#include<ShaderProgram.h>
using namespace std; 

class Mesh {
public:
	~Mesh();
	//Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index);
	Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index, glm::vec3 diffColor, glm::vec3 emisColor, glm::vec3 specColor, float shine);
	void render();
	void render(ShaderProgram* shader);
	void setup();
	unsigned int VBO, VAO, IBO;

private:
	vector<Vertex> _vertecies;
	vector<VertexAttribute> _attributes;
	vector<Index> _indicies;
	glm::vec3 _matDiffuse;
	glm::vec3 _matEmissive;
	glm::vec3 _matSpecular;
	float _shininess;
};
#endif