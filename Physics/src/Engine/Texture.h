#pragma once

class Texture
{
public:
	Texture(const char* path);
	void Bind();
private:
	unsigned int texture;
};