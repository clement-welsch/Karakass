#pragma once

#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& _path);
	~Texture();

	void Bind(unsigned int _slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;


};