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

void Renderable::render(ShaderProgram *shader) {

	for (size_t i = 0; i < meshList.size(); i++) {
		meshList[i].render(shader); 
	}

}
Renderable::~Renderable() {

}