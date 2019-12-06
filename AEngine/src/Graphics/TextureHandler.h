#pragma once

struct Texture
{
	GLuint textureId = 0;
	int width = 0;
	int height = 0;
	int colorChannels = 0;
};

class TextureHandler
{
public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	static TextureHandler* GetInstance();

	[[nodiscard]] static GLuint GetTextureId(const std::string& textureName)
	{
		const auto textureIt = textures.find(textureName);
		if (textureIt == textures.end()) return 0;
		return textureIt->second->textureId;
	}

	/*[[nodiscard]] inline Texture* GetTexture(const std::string& textureName)
	{
		return textures.find(textureName)->second;
	}*/

	static void CreateTexture(const std::string& textureName, const std::string& path);
	void Destroy() const;

private:
	TextureHandler() = default;
   ~TextureHandler();

	static std::map<std::string, std::unique_ptr<Texture>> textures;
	
	static std::unique_ptr<TextureHandler> instance;
	friend std::default_delete<TextureHandler>;
};