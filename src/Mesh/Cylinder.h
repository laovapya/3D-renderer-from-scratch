#pragma once
#include"Object3D.h"
#include"VertexData.h"
class Cylinder : public Object3D
{
public:
	Cylinder();
	VAO GetVAO() override;
};

