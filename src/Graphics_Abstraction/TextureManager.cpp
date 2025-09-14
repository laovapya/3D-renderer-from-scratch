#include "TextureManager.h"
#include <iostream>
#include <stb_image.h>

std::vector<GLuint> TextureManager::textures;

TextureManager::TextureManager()
{
	const int size = 64;
	unsigned char whitePixels[size * size * 4]; // RGBA
	for(int i = 0; i < size * size * 4; ++i)
		whitePixels[i] = 255; // full white + full alpha

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixels);
	textures.push_back(texture);
	//LoadTexture("assets/textures/wall.jpg");
}

int TextureManager::LoadTexture(const std::string& path)
{
	int width, height, channelsCount;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);
	if(!data)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
		return -1;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(channelsCount == 3) //rgb, rgba ?
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if(channelsCount == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "Unsupported number of channels: " << channelsCount << std::endl;

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	textures.push_back(texture);
	return (int)textures.size() - 1;
}

void TextureManager::BindTexture(int textureID, int unit)
{
	if(textureID < 0 || textureID >= textures.size())
		return;
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textures[textureID]);
}

void TextureManager::UnloadTexture(int textureID)
{
	if(textureID < 0 || textureID >= (int)textures.size())
		return;
	glDeleteTextures(1, &textures[textureID]);
	textures[textureID] = 0;
}

void TextureManager::UnloadAllTextures()
{
	for(int i = 0; i < (int)textures.size(); ++i)
	{
		UnloadTexture(i);
	}
	textures.clear();
}
