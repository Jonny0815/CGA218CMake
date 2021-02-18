#include <Mesh.h>
#include "Transform.h"
using namespace std;

enum class Type {
	Ground,Tree
};

class Renderable: public Transform {
public:
	Renderable::Renderable();
	Renderable::Renderable(vector<Mesh>, Type); 
	Renderable::~Renderable();
	void addMesh(Mesh);
	void addMeshes(vector<Mesh>);
	void render(ShaderProgram*, float);

	

private:
	vector<Mesh> meshList;

	Type type;

};