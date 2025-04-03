#pragma once
#include"Object3D.h"
class Sphere : public Object3D
{

public:

	Sphere();
	VAO GetVAO() override;
};