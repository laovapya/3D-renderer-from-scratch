#pragma once
#include"VAO.h"


//Define max value amount for different arrays

#define coneVertexCount 3 * 2 + 3 * 360 / 10 
#define cylinderVertexCount 3 * 2 + 2 * 3 * 360 / 10

#define coneIndexCount (360 / 10) * 3 * 2 
#define cylinderIndexCount 4 * (360 / 10) * 3 

#define max_grid_size 2 * 3 * 2 * 250


//VAO (vertex array object) stores vertex and index data, which is used to render 3D objects.
//using the same VAO for all shapes of the same type (cube, cone, cylinder, sphere)
//The VAO is retrieved from here.
class VertexData  
{
private:
	VertexData();

	//the amount of triangles in some shapes depend on this value
	int polygonAmount = 10; 

	//VAO of shapes
	VAO cubeVAO;
	VAO coneVAO;
	VAO cylinderVAO; 
	VAO sphereVAO;

	//the distance between grid lines
	float gridSpacing = 1;
	//VAO of grid lines
	VAO grid;
	//VAOs of x and z axises lines.
	VAO axisX;
	VAO axisZ;
	
	//algorythms to fill in the VAOs
	void SetCubeVAO();
	void SetConeVAO(); 
	void SetCylinderVAO();
	void SetSphereVAO();

	void SetGridVAO();

public:
	//multiply by this value to convert angles to radians.
	static float degToRad;
	
	//singleton 
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
	static VAO GetXVAO();
	static VAO GetZVAO();
	static VAO GetGridVAO();

	//get the index count corresponding to Objects (required by some GLFW functions)
	static int GetGridIndexCount();
	static int GetCubeIndexCount();
	static int GetConeIndexCount();
	static int GetCylinderIndexCount();
	static int GetSphereIndexCount();

};





