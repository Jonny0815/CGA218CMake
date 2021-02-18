#include "Scene.h"

using namespace glm;
Scene::Scene(GameWindow* window) :
	m_window(window)
{
	assert(window != nullptr);

	mv_cameras.push_back(new FreeCamera(m_window->getWindowWidth(), m_window->getWindowHeight(), 45.0, 0.1, 10.0));
	mv_cameras.push_back(new ThirdPersonCamera(m_window->getWindowWidth(), m_window->getWindowHeight(), 45.0, 0.1, 10.0));
}

Scene::~Scene()
{
	for (size_t i = 0; i < mv_cameras.size(); i++)
	{
		delete mv_cameras[i];
	}
}



bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("pixelEmitter", AssetManager::createShaderProgram("assets/shaders/pixelEmitterVertex.glsl", "assets/shaders/pixelEmitterFragment.glsl"));
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_assets.addShaderProgram("shader2", AssetManager::createShaderProgram("assets/shaders/vertex2.glsl", "assets/shaders/fragment2.glsl"));
		m_shaders = m_assets.getShaders();
		pixel = m_assets.getShaderProgram("pixelEmitter"); 
		regular = m_assets.getShaderProgram("shader"); 
		
		
		
		loadOBJtoRenderables("assets/models/ground.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader")));
		//loadOBJtoRenderables("assets/models/HQ_Movie cycle_lookY.obj", glm::vec3(0, 0.7, 0.6), glm::vec3(0.6, 0, 0.4), glm::vec3(1, 0, 1), 0.4);
		//loadOBJtoRenderables("assets/models/sphere.obj", glm::vec3(0.2, 0.7, 0.6), glm::vec3(0.6, 0.1, 0.1), glm::vec3(1,0,0), 0.2);
		//loadOBJtoRenderables("assets/models/sphere.obj", glm::vec3(0.2, 0.7, 0.6), glm::vec3(0.6, 0.1, 0.1), glm::vec3(1,0,0), 0.2);
		//loadOBJtoRenderables("assets/models/sphere.obj", glm::vec3(0.2, 0.7, 0.6), glm::vec3(0.6, 0.1, 0.1), glm::vec3(1,0,0), 0.2);
		//loadOBJtoRenderables("assets/models/sphere.obj", glm::vec3(0.2, 0.7, 0.6), glm::vec3(0.6, 0.1, 0.1), glm::vec3(1,0,0), 0.2);
		

		loadOBJtoRenderables("assets/models/sphere.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader2")));
		loadOBJtoRenderables("assets/models/sphere.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader2")));
		loadOBJtoRenderables("assets/models/sphere.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader2")));
		loadOBJtoRenderables("assets/models/sphere.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader2")));
		loadOBJtoRenderables("assets/models/sphere.obj", Material("assets/textures/red.png", "assets/textures/blue.png", "assets/textures/green.png", 0.2, false, m_assets.getShaderProgram("shader")));
		

		renderables[0].setScale(glm::vec3(0.10, 0.10, 0.10));
		//renderables[0].setScale(glm::vec3(100, 100, 100));
		vec3 angles(270, 0, 0);
		renderables[0].rotate(glm::quat(angles));
		renderables[0].setPosition(glm::vec3(0.0, -0.9, -0.5));
		renderables[1].setScale(glm::vec3(0.5, 0.4, 0.3));
		renderables[1].setPosition(glm::vec3(1.0, 0.4, 0.3));
		//renderables[1].setRotation(glm::quat(glm::vec3(glm::radians(-90.0), glm::radians(-90.0), 0)));
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

		pointLights.push_back(PointLight("test", glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));
		pointLights[0].translate(glm::vec3(1, 1, 1));
		pointLights[0].setParent(&renderables[1]);

		mv_cameras[0]->translate(vec3(0.0, 0.0, -2.0));
		//mv_cameras[0]->translate(vec3(2.0));

		//mv_cameras[1]->setParent(&renderables[1]);

		PixelEmitter *pixelEmitter = new PixelEmitter(pixel); 
		PixelEmitter *pixelEmitter2 = new PixelEmitter(pixel);
		pixelEmitter->setMaterial(Material("assets/textures/heart.png", "assets/textures/heart.png", "assets/textures/heart.png", 0.2, false, m_assets.getShaderProgram("pixelEmitter")));
		pixelEmitter2->setMaterial(Material("assets/textures/blue.png", "assets/textures/blue.png", "assets/textures/blue.png", 0.2, false, m_assets.getShaderProgram("pixelEmitter")));
		pixelEmitter->setParent(&renderables[1]); 
		pixelEmitter2->setPosition(vec3(0.0,1.0,1.0));
		pixelEmitters.push_back(pixelEmitter);
		pixelEmitters.push_back(pixelEmitter2);

		mv_cameras[1]->setParent(pixelEmitter);
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
int counter = 0; 
void Scene::render(float dt)
{

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT );
	//glClear(GL_STENCIL_BUFFER_BIT);

	if (changeCamera)
	{
		if (useCamera == 0)
		{
			useCamera = 1;
		}
		else
		{
			useCamera = 0;
		}

		changeCamera = false;
	}

	//for (auto it = m_shaders->begin(); it != m_shaders->end(); it++)
	//{
		//glVertexAttribDivisor(1, 0);
		//it->second.get()->use();


	regular->use();
	
	regular->setUniform("lightColorAmbient", ambientLight);

	for (size_t i = 0; i < pointLights.size(); i++)
	{
		pointLights[i].render(regular);
	}

	mv_cameras[useCamera]->render(regular);

	for (size_t i = 0; i < renderables.size(); i++)
	{
		renderables[i].render(regular, dt);
	}

	pixel->use();
	mv_cameras[useCamera]->render(pixel);
	for (size_t i = 0; i < pixelEmitters.size(); i++)
	{
		pixelEmitters[i]->render(pixel, dt);
	}
	
	//cout << dt << endl; 


	//}
	//pixelEmitter->render(dt, mv_cameras[useCamera]->getProjectionMatrix(), mv_cameras[useCamera]->getViewMatrix());

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
		renderables[1].translate(vec3(dt, 0, 0));
	}
	if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(0, dt, 0));
	}
	if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed)
	{
		renderables[1].translate(vec3(-dt, 0, 0));
	}

	if (m_window->getInput().getKeyState(Key::K) == KeyState::Pressed)
	{
		pointLights[0].translate(vec3(0, -dt, 0));
	}
	if (m_window->getInput().getKeyState(Key::J) == KeyState::Pressed)
	{
		pointLights[0].translate(vec3(dt, 0, 0));
	}
	if (m_window->getInput().getKeyState(Key::I) == KeyState::Pressed)
	{
		pointLights[0].translate(vec3(0, dt, 0));
	}
	if (m_window->getInput().getKeyState(Key::L) == KeyState::Pressed)
	{
		pointLights[0].translate(vec3(-dt, 0, 0));
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
		vec3 angles(0, dt, 0);
		renderables[1].rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::Q) == KeyState::Pressed)
	{
		vec3 angles(0, -dt, 0);
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
		mv_cameras[useCamera]->translate(vec3(0.0, dt, 0.0));
	}
	if (m_window->getInput().getKeyState(Key::Down) == KeyState::Pressed)
	{
		mv_cameras[useCamera]->translate(vec3(0.0, -dt, 0.0));
	}

	if (m_window->getInput().getKeyState(Key::Right) == KeyState::Pressed)
	{
		mv_cameras[useCamera]->translate(vec3(-dt, 0.0, 0.0));
	}
	if (m_window->getInput().getKeyState(Key::Left) == KeyState::Pressed)
	{
		mv_cameras[useCamera]->translate(vec3(dt, 0.0, 0.0));
	}

	if (m_window->getInput().getKeyState(Key::PageUp) == KeyState::Pressed)
	{
		mv_cameras[useCamera]->translate(vec3(0.0, 0.0, dt));
	}
	if (m_window->getInput().getKeyState(Key::PageDown) == KeyState::Pressed)
	{
		mv_cameras[useCamera]->translate(vec3(0.0, 0.0, -dt));
	}

	//rotate cam

	if (m_window->getInput().getKeyState(Key::NumPad2) == KeyState::Pressed)
	{
		vec3 angles(-dt, 0, 0);
		mv_cameras[useCamera]->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad8) == KeyState::Pressed)
	{
		vec3 angles(dt, 0, 0);
		mv_cameras[useCamera]->rotate(angles);
	}

	if (m_window->getInput().getKeyState(Key::NumPad4) == KeyState::Pressed)
	{
		vec3 angles(0, -dt, 0);
		mv_cameras[useCamera]->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad6) == KeyState::Pressed)
	{
		vec3 angles(0, dt, 0);
		mv_cameras[useCamera]->rotate(angles);
	}

	if (m_window->getInput().getKeyState(Key::NumPad7) == KeyState::Pressed)
	{
		vec3 angles(0, 0, -dt);
		mv_cameras[useCamera]->rotate(angles);
	}
	if (m_window->getInput().getKeyState(Key::NumPad9) == KeyState::Pressed)
	{
		vec3 angles(0, 0, dt);
		mv_cameras[useCamera]->rotate(angles);
	}

}

GameWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{
	if (key == Key::Space && action == Action::Down)
	{
		changeCamera = true;
	}
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

void Scene::loadOBJtoRenderables(string path, Material mat)
{
	vector<Mesh> meshesFromObj;

	OBJResult obRes = OBJLoader::loadOBJ(path, false, false);
	for (size_t i = 0; i < obRes.objects[0].meshes.size(); i++) {
		OBJMesh m = obRes.objects[0].meshes[i];
		vector<VertexAttribute> va = m.atts;
		vector<Vertex> v = m.vertices;
		vector<Index> ind = m.indices;
		Mesh me(v, va, ind, mat);
		meshesFromObj.push_back(me);
	}

	renderables.push_back(Renderable(meshesFromObj));

	 return;
}
