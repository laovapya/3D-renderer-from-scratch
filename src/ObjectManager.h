#pragma once
#include"Object3D.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"
#include"Lightsource.h"

#include<vector>
#include <string>





class ObjectManager
{
private:

	int objectCount = 0;


	int cubeCount = 0;
	int coneCount = 0;
	int cylinderCount = 0;
	int sphereCount = 0;

	int lightsourceCount = 0;
	int cameraCount = 0;

	int segmentCount = 12;

	std::vector<std::unique_ptr<Object3D>> createdObjects;

	

	void DeleteObject(Object3D* object);
	int AddObject(std::unique_ptr<Object3D> object);
public:

	ObjectManager();


	//Adding new objects
	int AddCube();
	int AddCone();
	int AddCylinder();
	int AddSphere();

	int AddLightsource(); 
	
	
	void RemoveObject(int id);
	void RemoveSelectedObjects();

	void SetSegmentCount(int count);


	const std::vector<std::unique_ptr<Object3D>>& GetCreatedObjects();

	const std::vector<glm::vec3> GetLightsourcePositions() const;
	const std::vector<glm::vec3> GetLightsourceColors() const;
};

