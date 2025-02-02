#pragma once
#include"Shape.h"
#include"ObjectManager.h"
#include"Window.h"
//This class renders all the objects in the scene
class Scene
{
private:
	//The scene is a part of window, so we need an window instance to run it.
	Window* window;

	//object manager and camera are a part of the scene, we dont initialize these objects anywhere else. 
	ObjectManager manager;
	
	//Draw scene grid. Is called each frame
	void DrawGrid();
public:
	Scene(Window* window);

	//delete VertexData VAOs.
	~Scene();

	//draw scene objects. Is called each frame.
	void Update();




	Window* GetWindow();
	ObjectManager* GetObjectManager();

};



