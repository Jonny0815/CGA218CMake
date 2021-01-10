#include <Renderable.h>

Renderable::Renderable() {

}
Renderable::Renderable(vector<Mesh> meshes) {
	meshList = meshes; 
}
void Renderable::addMesh(Mesh mesh) {
	meshList.push_back(mesh); 
}
void Renderable::addMeshes(vector<Mesh> meshes) {
	for (size_t i = 0; i < meshes.size(); i++) {
		meshList.push_back(meshes[i]);
	}
}

void Renderable::render(ShaderProgram *shader, float dt) {

	shader->use();
	shader->setUniform("dt", dt);

	glm::mat4 parentMat(1.0);
	Transform* akt = this;
	while (akt->getParent() != nullptr)
	{
		akt = akt->getParent();
		parentMat = akt->getTransformMatrix() * parentMat;
	}

	shader->setUniform("model", parentMat*getTransformMatrix(), false);

	for (size_t i = 0; i < meshList.size(); i++) {
		
		meshList[i].render(shader); 
	}

}
Renderable::~Renderable() {

}