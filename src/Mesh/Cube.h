#pragma once
#include"Object3D.h"
class Cube : public Object3D
{
public:
	VAO GetVAO() const override;
	Cube();
	
};