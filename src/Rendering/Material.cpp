#include "Material.h"

const Vector3 Material::selectColor = Vector3(0.0f, 0.3f, 0.65f); // blue
Material::Material()
{
	color = Vector3(1.0f, 1.0f, 1.0f);
	colorAlpha = 1.0f;
	isLit = true;
}

Material::Material(const Vector3& color, float colorAlpha, bool isLit)
{
	this->color = color;
	this->colorAlpha = colorAlpha;
	this->isLit = isLit;

	textureID = 0;
	SetTexture(textureID);
}

void Material::SetTexture(unsigned int id)
{
	textureID = id;
}

// void Material::BindTexture() const
// {
// 	TextureManager::BindTexture(textureID, textureUnit);
// }
Vector3 Material::GetColor() const
{
	return color;
}

void Material::SetColor(const Vector3& color)
{
	this->color = color;
	this->colorAlpha = 1.0f;
}

void Material::SetColor(const Vector3& color, float alpha)
{
	this->color = color;
	this->colorAlpha = alpha;
}

void Material::SetColor(float r, float g, float b, float alpha)
{
	this->color = Vector3(r, g, b);
	this->colorAlpha = alpha;
}

bool Material::GetIfLit() const
{
	return isLit;
}
