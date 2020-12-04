#include <Mesh.h>
#include "Transform.h"
using namespace std;

class Renderable: public Transform {
public:
	Renderable::Renderable();
	Renderable::Renderable(vector<Mesh>); 
	Renderable::~Renderable();
	void addMesh(Mesh);
	void addMeshes(vector<Mesh>);
	void render(ShaderProgram*, float);

	

private:
	vector<Mesh> meshList;

	

};