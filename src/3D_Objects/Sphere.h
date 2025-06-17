#pragma once

#include "Object3D.h"

class Sphere : public Object3D
{

public:
	VAO GenerateVAO(int& indexCount, int segmentCount = 12) const override;
	Sphere(int segmentCount);
};