#pragma once
#include "Object3D.h"
class Lightsource : public Object3D
{
public:
	VAO GenerateVAO(int& indexCount, int segmentCount = 0) const override;

	void Scale(glm::vec3 v) override;

	void Scale(const float* const v) override;
	Lightsource();
};