#pragma once
#include "Object3D.h"
class Cone : public Object3D
{

public:
	VAO GenerateVAO(int& indexCount, int segmentCount = 10)
		const override; //put overriden methods before constructor (compiler bug ?)
	Cone(int segmentCount);
};