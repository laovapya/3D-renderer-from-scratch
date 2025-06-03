#pragma once
#include"Object3D.h"
#include"ObjectManager.h"
#include"Window.h"
//This class renders all the objects in the scene
class Scene
{
private:
	//The scene is a part of window, so we need an window instance to run it.
	const Window* window;
	Camera* currentCamera;
	Object3D* currentLight;

	//object manager and camera are a part of the scene, dont initialize these objects anywhere else. 
	ObjectManager manager; 
	
	const Shader* litShader; //uses normals for lighting
	const Shader* defaultShader; 

	void DrawGrid();
public:
	Scene(const Window* window);

	//delete VertexData VAOs.
	~Scene();

	//draw scene objects. Is called each frame.
	void Update();




	//const Window* GetWindow() const;
	ObjectManager* GetObjectManager();

};



