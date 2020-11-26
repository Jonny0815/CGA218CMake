#include "Scene.h"
#include <AssetManager.h>



Scene::Scene(GameWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */

		float vertices[] = {-0.5, -0.5, 0.0, 0.0, 1.0,
							0.5, -0.5, 0.0, 0.0, 1.0,
							0.5, 0.5, 0.0, 1.0, 0.0,
							-0.5, 0.5, 0.0, 1.0, 0.0,
							0.0, 1.0, 1.0, 0.0, 0.0};
		
		int indices[] = {	0, 1, 2,
							0, 2, 3,
							4, 2, 3
		};

		glGenVertexArrays(1,&vaoID);
		glGenBuffers(1, &vboID);
		glGenBuffers(1, &iboID);


		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//initial opengl state
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        std::cout << "Scene initialization done\n";

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
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader->use();

    /*
    * ************
    * Place your code here!
    * ************
    */

	glBindVertexArray(vaoID);

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

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