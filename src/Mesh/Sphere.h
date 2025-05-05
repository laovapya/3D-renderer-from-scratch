#pragma once

#include"Object3D.h"


class Sphere : public Object3D
{

public:
	VAO GetVAO() const override;
	Sphere();
	
};