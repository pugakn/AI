#pragma once
#include "json.hpp"
#include <string>

struct Frame
{
	int16_t x,y,w,h;
	bool rotated, trimmed;
	int16_t spriteSourceSizeX, spriteSourceSizeY, spriteSourceSizeW, spriteSourceSizeH;
	int16_t sourceSizeW, sourceSizeH;
};
class JSONToBinary
{
public:
	void ToBinary(nlohmann::json jsonFile,std::string fileName);
	JSONToBinary();
	~JSONToBinary();
};

