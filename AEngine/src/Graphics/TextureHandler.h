#pragma once

#include <Core/AEpch.h>

class TextureHandler
{
public:
	struct Texture 
	{
		GLuint textureId = 0;
		int width = 0;
		int height = 0;
		int colorChannels = 0;
	};

	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	static TextureHandler* GetInstance();

	[[nodiscard]] inline GLuint GetTextureId(std::string textureName)
	{
		const auto textureIter = textures.find(textureName);
		if(textureIter == textures.end()) return 0;
		return textureIter->second->textureId;
	}

	[[nodiscard]] inline Texture* GetTexture(std::string textureName)
	{
		return textures.find(textureName)->second;
	}

	void CreateTexture(const std::string& textureName, const std::string& path);

private:
	TextureHandler() = default;
	~TextureHandler();

	static std::unique_ptr<TextureHandler> instance;
	static std::map<std::string, Texture*> textures;
	friend std::default_delete<TextureHandler>;
};