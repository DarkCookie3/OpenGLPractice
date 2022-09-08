#include "Texture.h"

#include "stb_image.h"

std::unordered_map<unsigned int, int> Texture::numOfInstances;

Texture::Texture(const std::string& path, TextureType type)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), m_TexType(type)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	numOfInstances[m_RendererID] = 1;
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::Texture(int height, int width, TextureType type)
	: m_RendererID(0), m_FilePath(), m_LocalBuffer(nullptr), m_Width(width), m_Height(height), m_BPP(4), m_TexType(type)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const Texture& arg) noexcept
	: m_FilePath(arg.m_FilePath), m_LocalBuffer(arg.m_LocalBuffer),
	m_Width(arg.m_Width), m_Height(arg.m_Height), m_BPP(arg.m_BPP), m_TexType(arg.m_TexType)
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	numOfInstances[m_RendererID] += 1;
}

Texture::Texture(Texture&& arg) noexcept
	: m_FilePath(arg.m_FilePath), m_LocalBuffer(arg.m_LocalBuffer),
	m_Width(arg.m_Width), m_Height(arg.m_Height), m_BPP(arg.m_BPP), m_TexType(arg.m_TexType)
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	arg.m_RendererID = 0;
}

Texture& Texture::operator=(const Texture& arg) noexcept
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	m_FilePath = arg.m_FilePath;
	m_LocalBuffer = arg.m_LocalBuffer;
	m_Width = arg.m_Width;
	m_Height = arg.m_Height;
	m_BPP = arg.m_BPP;
	m_TexType = arg.m_TexType;
	numOfInstances[m_RendererID] += 1;
	return *this;
}

Texture& Texture::operator=(Texture&& arg) noexcept
{
	numOfInstances[m_RendererID] -= 1;
	m_RendererID = arg.m_RendererID;
	m_FilePath = arg.m_FilePath;
	m_LocalBuffer = arg.m_LocalBuffer;
	m_Width = arg.m_Width;
	m_Height = arg.m_Height;
	m_BPP = arg.m_BPP;
	m_TexType = arg.m_TexType;
	arg.m_RendererID = 0;
	return *this;
}


Texture::~Texture()
{
	if (m_RendererID != 0)
	{
		if (numOfInstances[m_RendererID] == 1 && m_RendererID != 0)
		{
			GLCall(glDeleteTextures(1, &m_RendererID));
		}
		numOfInstances[m_RendererID] -= 1;
	}
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
