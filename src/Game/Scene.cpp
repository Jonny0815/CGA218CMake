#include "Scene.h"

using namespace glm;
Scene::Scene(GameWindow * window) :
	m_window(window)
{
	assert(window != nullptr);

	m_cam = new Camera(m_window->getWindowWidth(), m_window->getWindowHeight(), 45.0, 0.1, 10.0);

}

Scene::~Scene()
{
	delete m_cam;
}


vector<Renderable> renderables;
vector<Mesh> meshesFromObj;
vector<Mesh> meshesFromObj2;



bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");

		

		OBJResult obRes2 = OBJLoader::loadOBJ("assets/models/ground.obj", false, false);

		for (size_t i = 0; i < obRes2.objects[0].meshes.size(); i++) {
			OBJMesh m = obRes2.objects[0].meshes[i];
			vector<VertexAttribute> va = m.atts;
			vector<Vertex> v = m.vertices;
			vector<Index> ind = m.indices;
			Mesh me(v, va, ind);
			meshesFromObj2.push_back(me);
		}
		renderables.push_back(Renderable(meshesFromObj2));

		OBJResult obRes = OBJLoader::loadOBJ("assets/models/sphere.obj", false, false);
		for (size_t i = 0; i < obRes.objects[0].meshes.size(); i++) {
			OBJMesh m = obRes.objects[0].meshes[i];
			vector<VertexAttribute> va = m.atts;
			vector<Vertex> v = m.vertices;
			vector<Index> ind = m.indices;
			Mesh me(v, va, ind);
			meshesFromObj.push_back(me);
		}
		renderables.push_back(Renderable(meshesFromObj));
		renderables.push_back(Renderable(meshesFromObj));
		renderables.push_back(Renderable(meshesFromObj));
		renderables.push_back(Renderable(meshesFromObj));
		renderables.push_back(Renderable(meshesFromObj));

		renderables[0].setScale(glm::vec3(0.01, 0.01, 0.01));
		vec3 angles(270, 0, 0);
		renderables[0].rotate(glm::quat(angles));
		renderables[0].setPosition(glm::vec3(0.0, -0.9, -0.5));
		renderables[1].setScale(glm::vec3(0.5, 0.4, 0.3));
		renderables[2].setScale(glm::vec3(0.3, 0.4, 0.2));
		renderables[2].setPosition(glm::vec3(0.8, 0.7, 0));
		renderables[3].setScale(glm::vec3(0.2, 0.3, 0.4));
		renderables[3].setPosition(glm::vec3(-0.8, 0.7, 0));
		renderables[4].setPosition(glm::vec3(-0.7, 0.8, 0.0));

		renderables[2].setParent(&renderables[1]);
		renderables[3].setParent(&renderables[1]);
		renderables[4].setParent(&renderables[3]);

		renderables[5].setScale(glm::vec3(0.1, 0.3, 0.2));
		renderables[5].setPosition(glm::vec3(0.5, 0.2, 2));

		m_cam->translate(vec3(0.0, 0.0, -2.0));
		m_cam->bind(m_shader);

		m_cam->setParent(&renderables[1]);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

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

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_cam->render();

	for (size_t i = 0; i < renderables.size(); i++)
	{
		renderables[i].render(m_shader, dt);
	}

}

void Scene::update(float dt)
{

	//move balls

	if (m_window->getInput().getKeyState(Key::S) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(0, -dt, 0));
	}
	if (m_window->getInput().getKeyState(Key::A) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(-dt, 0, 0));
	}
	if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(0, dt, 0));
	}
	if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(dt, 0, 0));
	}

	if (m_window->getInput().getKeyState(Key::LeftCtrl) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(0, 0, -dt));
	}
	if (m_window->getInput().getKeyState(Key::LeftShift) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(0, 0, dt));
	}

	//rotate balls

	if (m_window->getInput().getKeyState(Key::E) == KeyState::Pressed)
	{
		vec3 angles(dt, 0, 0);
		renderables[1].rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::Q) == KeyState::Pressed)
	{
		vec3 angles(-dt, 0, 0);
		renderables[1].rotate(angles);
	}

	//scale balls

	if (m_window->getInput().getKeyState(Key::R) == KeyState::Pressed)
	{
		renderables[1].scale(vec3(1+dt,1+dt,1+dt));
	}
	if (m_window->getInput().getKeyState(Key::F) == KeyState::Pressed)
	{
		renderables[1].scale(vec3(1-dt, 1-dt, 1-dt));
	}


	//move cam

	if (m_window->getInput().getKeyState(Key::Up) == KeyState::Pressed)
	{
		m_cam->translate(vec3(0.0, dt, 0.0));
	}
	if (m_window->getInput().getKeyState(Key::Down) == KeyState::Pressed)
	{
		m_cam->translate(vec3(0.0, -dt, 0.0));
	}

	if (m_window->getInput().getKeyState(Key::Right) == KeyState::Pressed)
	{
		m_cam->translate(vec3(-dt, 0.0, 0.0));
	}
	if (m_window->getInput().getKeyState(Key::Left) == KeyState::Pressed)
	{
		m_cam->translate(vec3(dt, 0.0, 0.0));
	}

	if (m_window->getInput().getKeyState(Key::PageUp) == KeyState::Pressed)
	{
		m_cam->translate(vec3(0.0, 0.0, dt));
	}
	if (m_window->getInput().getKeyState(Key::PageDown) == KeyState::Pressed)
	{
		m_cam->translate(vec3(0.0, 0.0, -dt));
	}

	//rotate cam

	if (m_window->getInput().getKeyState(Key::NumPad2) == KeyState::Pressed)
	{
		vec3 angles(-dt, 0, 0);
		m_cam->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad8) == KeyState::Pressed)
	{
		vec3 angles(dt, 0, 0);
		m_cam->rotate(angles);
	}

	if (m_window->getInput().getKeyState(Key::NumPad4) == KeyState::Pressed)
	{
		vec3 angles(0, -dt, 0);
		m_cam->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad6) == KeyState::Pressed)
	{
		vec3 angles(0, dt, 0);
		m_cam->rotate(angles);
	}

	if (m_window->getInput().getKeyState(Key::NumPad7) == KeyState::Pressed)
	{
		vec3 angles(0, 0, -dt);
		m_cam->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad9) == KeyState::Pressed)
	{
		vec3 angles(0, 0, dt);
		m_cam->rotate(angles);
	}

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