#pragma once
#include"Object3D.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"
#include"Lightsource.h"
//#include"Camera.h" //when it will be Object3D
#include<vector>

//defining max amount of objects in the scene
#define maxCount 32

//this class manages the container with all created objects.
//it has functionality to add, remove, select, deselect objects.

class ObjectManager
{
private:
	//current object amount
	int objectCount = 0;

	const int COUNT = maxCount;

	//The scene's objects container
	std::vector<Object3D*> createdObjects;


	void AddObject(Object3D* object);
public:

	ObjectManager();
	~ObjectManager();

	//Adding new objects
	int AddCube();
	int AddCone();
	int AddCylinder();
	int AddSphere();

	int AddLightsource(); 
	int AddCamera(); 

	void RemoveObject(int id);

	//Selecting objects 
	void SelectObject(int id);
	void DeselectObject(int id);

	std::vector<Object3D*> GetCreatedObjects();
};

