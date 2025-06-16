#pragma once
#include"Object3D.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"
#include"Lightsource.h"
//#include"Camera.h" //when it will be Object3D
#include<vector>
#include <string>
//defining max amount of objects in the scene
#define maxCount 32

//this class manages the container with all created objects.
//it has functionality to add, remove, select, deselect objects.

class ObjectManager
{
private:
	//current object amount
	
	int objectCount = 0;

	//current count of shapes (used to create names in the object menu list)
	int cubeCount = 0;
	int coneCount = 0;
	int cylinderCount = 0;
	int sphereCount = 0;

	int lightsourceCount = 0;
	int cameraCount = 0;

	const int COUNT = maxCount;

	//mesh divisions count
	int segmentCount = 12;
	//The scene's objects container
	std::vector<Object3D*> createdObjects;

	

	void DeleteObject(Object3D* object);
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
	void RemoveSelectedObjects();

	void SetSegmentCount(int count);
	//Selecting objects 
	//void SelectObject(int id);
	//void DeselectObject(int id);

	std::vector<Object3D*> GetCreatedObjects();

	const std::vector<glm::vec3> GetLightsourcePositions() const;
	const std::vector<glm::vec3> GetLightsourceColors() const;// considering updating positions and colors with events 
};

