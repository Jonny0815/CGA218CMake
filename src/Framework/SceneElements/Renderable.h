#include <Mesh.h>
using namespace std;

class Renderable {
public:
	Renderable::Renderable();
	Renderable::Renderable(vector<Mesh>); 
	Renderable::~Renderable();
	void addMesh(Mesh);
	void addMeshes(vector<Mesh>);
	void render(ShaderProgram*);
private:
	vector<Mesh> meshList;
};