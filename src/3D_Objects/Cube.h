#pragma once
#include "Object3D.h"
class Cube : public Object3D
{
public:
	VAO GenerateVAO(int& indexCount, int segmentCount = 0) const override;
	Cube();
};