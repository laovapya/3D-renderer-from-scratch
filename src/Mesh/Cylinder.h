#pragma once
#include"Object3D.h"

class Cylinder : public Object3D
{
public:
	VAO GetVAO() const override;
	Cylinder();
	
};