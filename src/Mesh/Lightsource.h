#pragma once
#include"Object3D.h"
class Lightsource : public Object3D
{
public:

	Lightsource();
	VAO GetVAO() override;

	void Scale(glm::vec3 v) override;

	void Scale(float* v) override;
};
