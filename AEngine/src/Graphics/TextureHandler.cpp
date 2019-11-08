#include "Core/AEpch.h"
#include "TextureHandler.h"
#include "Core/Logger.h"

std::unique_ptr<TextureHandler> TextureHandler::instance(nullptr);
std::map<std::string, TextureHandler::Texture*> TextureHandler::textures = std::map<std::string, TextureHandler::Texture*>();

TextureHandler::~TextureHandler() 
{
	if(!textures.empty()) 
	{
		for (auto texture : textures) 
		{
			glDeleteTextures(1, &texture.second->textureId);
			delete texture.second, texture.second = nullptr;
		}

		textures.clear();
	}
}

TextureHandler* TextureHandler::GetInstance()
{
	if(!instance) instance = std::unique_ptr<TextureHandler>(new TextureHandler());
	return instance.get();
}

void TextureHandler::CreateTexture(const std::string& textureName, const std::string& path)
{
	auto texture = new Texture();
	auto data = stbi_load(path.c_str(), &texture->width, &texture->height, &texture->colorChannels, 0);

	if(!data) 
	{
		LOG_ERROR("Failed to load texture: " + textureName, "TextureHandler.cpp", __LINE__);
		return;
	}

	glGenTextures(1, &texture->textureId);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);

	const auto mode = texture->colorChannels == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, texture->width, texture->height, 0, mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	textures[textureName] = texture;
	stbi_image_free(data);
	data = nullptr; 
}
