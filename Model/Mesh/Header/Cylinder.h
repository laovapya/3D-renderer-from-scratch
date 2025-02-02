#pragma once
#include"Shape.h"
#include"VertexData.h"
class Cylinder : public Shape
{
public:
	Cylinder();
	VAO GetVAO() override;
};

