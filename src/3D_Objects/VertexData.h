#pragma once
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "math.h"

#include <glm/glm.hpp>
#include <vector>

#include <iostream>

//this class contains VAO data that doesnt need to be transformed.
class VertexData
{
private:
	VertexData();

	//the distance between grid lines
	float gridSpacing = 1;
	float maxGridSize = 2 * 3 * 2 * 250;

	int gridIndexCount;

	VAO grid;
	VAO axisX;
	VAO axisZ;

	void SetGridVAO();

public:
	VertexData(const VertexData&) = delete;
	static VertexData& GetInstance()
	{
		static VertexData instance;
		return instance;
	}
	static VAO GetXaxisVAO();
	static VAO GetZaxisVAO();
	static VAO GetGridVAO();

	static int GetGridIndexCount();
};
