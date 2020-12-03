#include "Scene.h"
using namespace glm;
Scene::Scene(GameWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}


Renderable renderable; 
vector<Mesh> meshesFromObj;
bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");

		OBJResult obRes = OBJLoader::loadOBJ("assets/models/sphere.obj",false,false);
		for (size_t i = 0; i < obRes.objects[0].meshes.size(); i++) {
			OBJMesh m = obRes.objects[0].meshes[i];
			vector<VertexAttribute> va = m.atts; 
			vector<Vertex> v = m.vertices; 
			vector<Index> ind = m.indices; 
			Mesh me(v, va, ind);
			meshesFromObj.push_back(me);
		}
		renderable = Renderable(meshesFromObj); 

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        std::cout << "Scene initialization done\n";
		glEnable(GL_CULL_FACE); 
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK); 
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::shutdown()
{

}

void Scene::render(float dt)
{
	renderable.render(m_shader, dt); 

}

void Scene::update(float dt)
{

}

GameWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}