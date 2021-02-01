#pragma once

#include "GameWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include <CommonTypes.h>
#include <Mesh.h>
#include <Renderable.h>
#include <OBJLoader.h>
#include "FreeCamera.h"
#include "ThirdPersonCamera.h"
#include "PointLight.h"

class Scene
{
public:
	Scene(GameWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	GameWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	vector<Camera*> mv_cameras;
	int useCamera = 0;
	bool changeCamera = false;
	GameWindow* m_window;
	AssetManager m_assets;
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>* m_shaders;
    GLuint vaoID, vboID;

	glm::vec3 ambientLight{ 0.5,0.5,0.5 };

	vector<Renderable> renderables;
	vector<PointLight> pointLights;

	void loadOBJtoRenderables(string path, Material mat);

};

