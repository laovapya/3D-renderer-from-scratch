#pragma once
#include"Object3D.h"
class Cone : public Object3D
{

public:
	VAO GetVAO() const override; //put overriden methods before constructor (compiler bug ?)
	Cone();
};