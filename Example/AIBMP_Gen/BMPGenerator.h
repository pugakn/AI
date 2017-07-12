#pragma once
#include <functional>
#include <vector>
struct C_RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	C_RGB() {};
	C_RGB(uint8_t r, uint8_t g, uint8_t b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class CBMPGenerator
{

public:
	CBMPGenerator();
	~CBMPGenerator();
	void SaveBitmap(const char* name,size_t width, size_t height, std::function<C_RGB(int x,int y)> fn);
};

