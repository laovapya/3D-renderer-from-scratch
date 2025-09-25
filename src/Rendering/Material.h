#pragma once
#include <glad/glad.h>
//#include "Graphics_Abstraction/TextureManager.h"
#include "Utility/Vector3.h"
class Material
{
private:
	Vector3 color;
	float colorAlpha = 1.0f;
	bool isLit;

	int textureUnit = 0;
	unsigned int textureID = 0;

public:
	Material();
	Material(const Vector3& color, float colorAlpha, bool isLit);

	Vector3 GetColor() const;
	void SetColor(const Vector3& color);
	void SetColor(const Vector3& color, float alpha);
	void SetColor(float r, float g, float b, float alpha);

	bool GetIfLit() const;

	// void BindTexture() const;
	void SetTexture(unsigned int id);
	int GetTextureID() const
	{
		return textureID;
	}
	const static Vector3 selectColor;
};
