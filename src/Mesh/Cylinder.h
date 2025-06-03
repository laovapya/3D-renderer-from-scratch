#pragma once
#include"Object3D.h"

class Cylinder : public Object3D
{
public:
	VAO GenerateVAO(int& indexCount, int segmentCount = 10) const override;
	Cylinder(int segmentCount);
	
};