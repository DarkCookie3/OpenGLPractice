#pragma once

#include "Renderer.h"


enum class TextureType
{
	undefined = 0,
	diffuse,
	specular,
	frame
};


class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	TextureType m_TexType;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	static std::unordered_map<unsigned int, int> numOfInstances;
public:
	Texture(const std::string& path, TextureType type);
	Texture(int height, int width, TextureType type);
	Texture(const Texture& arg) noexcept;
	Texture(Texture&& arg) noexcept;

	Texture& operator=(const Texture& arg) noexcept;
	Texture& operator=(Texture&& arg) noexcept;

	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline TextureType GetType() const
	{
		return m_TexType;
	}
	inline std::string GetPath() const
	{
		return m_FilePath;
	}
	inline int GetWidth() const
	{
		return m_Width;
	}
	inline int GetHeight() const
	{
		return m_Height;
	}
};