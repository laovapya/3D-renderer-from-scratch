#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>

class TextureManager
{
public:
	static int LoadTexture(const std::string& path);

	static void BindTexture(int textureID, int unit = 0);

	static void UnloadTexture(int textureID);
	static void UnloadAllTextures();
	TextureManager(const TextureManager&) = delete;
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}
	static std::vector<GLuint> textures;

private:
	TextureManager();
};
