#pragma once
#include"Object3D.h"
class Cone : public Object3D
{

public:
	VAO GetVAO() override;
	Cone();
};

