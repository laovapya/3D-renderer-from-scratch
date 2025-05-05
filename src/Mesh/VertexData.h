#pragma once
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"math.h"

#include<vector>
#include<glm/glm.hpp> 


#include<iostream>
//the idea was to have a singletone class that inits all the mesh data only once 


//VAO (vertex array object) stores vertex and index data, which is used to render 3D objects.
//using the same VAO for all shapes of the same type (cube, cone, cylinder, sphere)
//The VAO is retrieved from here.
class VertexData  
{
private:
	VertexData();

	//the amount of triangles in some objects depend on this value
	int polygonAmount = 10; 

	//VAO of shapes
	VAO cubeVAO;
	VAO coneVAO;
	VAO cylinderVAO; 
	VAO sphereVAO;

	//the distance between grid lines
	float gridSpacing = 1;
	float maxGridSize = 2 * 3 * 2 * 250;

	int gridIndexCount;
	int cubeIndexCount;
	int ConeIndexCount;
	int CylinderIndexCount;
	int SphereIndexCount;
	

	VAO grid;
	VAO axisX;
	VAO axisZ;
	
	//algorithms to fill in the VAOs
	void SetCubeVAO();
	void SetConeVAO(); 
	void SetCylinderVAO();
	void SetSphereVAO();

	void SetGridVAO();

	std::vector<float> CalculateNormals(const std::vector<float>& vertices, const std::vector<int>& indices);
	//std::vector<float> CombineVerticesNormals(const std::vector<float>& vertices, const std::vector<glm::vec3>& normals, const std::vector<int>& indices);
public:
	
	static float degToRad; //multiply by this value to convert angles to radians.
	
	//singleton because we dont want to init data each time new object is created (currently the class builds most meshes) 
	VertexData(const VertexData&) = delete;
	static VertexData& GetInstance() {
		static VertexData instance;
		return instance;
	}

	//get the VAO (to bind it and draw an object)
	static VAO GetCubeVAO();
	static VAO GetConeVAO(); 
	static VAO GetCylinderVAO();
	static VAO GetSphereVAO();
	static VAO GetXaxisVAO();
	static VAO GetZaxisVAO();
	static VAO GetGridVAO();

	//get the index count corresponding to Objects (required by some GLFW functions)
	static int GetGridIndexCount();
	static int GetCubeIndexCount();
	static int GetConeIndexCount();
	static int GetCylinderIndexCount();
	static int GetSphereIndexCount();

};





