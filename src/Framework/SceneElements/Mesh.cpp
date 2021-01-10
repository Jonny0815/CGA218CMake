#include<Mesh.h>
#include <AssetManager.h>



//Mesh::Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index ) {
//		_vertecies = vertecies;
//		_attributes = attributes;
//		_indicies = index; 
//		setup(); 
//}
Mesh::Mesh(vector<Vertex> vertecies, vector<VertexAttribute> attributes, vector<Index> index, glm::vec3 diffColor, glm::vec3 emisColor, glm::vec3 specColor, float shine)
{
	_vertecies = vertecies;
	_attributes = attributes;
	_indicies = index;
	_matDiffuse = diffColor;
	_matEmissive = emisColor;
	_matSpecular = specColor;
	_shininess = shine;
	setup();
}


void Mesh::render(ShaderProgram* shader)
{

	shader->use();
	shader->setUniform("matDiffuse", _matDiffuse);
	shader->setUniform("matEmissive", _matEmissive);
	shader->setUniform("matSpecular", _matSpecular);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, _indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

	
void Mesh::setup() {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER,_vertecies.size() * sizeof(Vertex), &_vertecies[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicies.size() * sizeof(GLuint), &_indicies[0], GL_STATIC_DRAW);

			//position
			for (size_t i = 0; i < _attributes.size(); i++) {
				VertexAttribute attribute = _attributes[i]; 
				glVertexAttribPointer(i, attribute.n, attribute.type, GL_FALSE, attribute.stride, (void*)attribute.offset);
				glEnableVertexAttribArray(i);
			}

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
		
}

Mesh::~Mesh() {

}

