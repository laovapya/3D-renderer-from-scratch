#pragma once
#include"Shape.h"
class Cube : public Shape
{
public:

	Cube();
	VAO GetVAO() override;
};
