#include "stdafx.h"
#include "JSONToBinary.h"
#include <fstream>
using namespace std;
void JSONToBinary::ToBinary(nlohmann::json jsonFile, std::string fileName)
{
	vector<Frame> frames;
	uint16_t attackN = 0;
	uint16_t attackNW = 0;
	uint16_t attackS = 0;
	uint16_t attackSW = 0;
	uint16_t attackW = 0;
	uint16_t dieN = 0;
	uint16_t dieNW = 0;
	uint16_t dieS = 0;
	uint16_t dieSW = 0;
	uint16_t dieW = 0;
	uint16_t idleN = 0;
	uint16_t idleNW = 0;
	uint16_t idleS = 0;
	uint16_t idleSW = 0;
	uint16_t idleW = 0;
	uint16_t runN = 0;
	uint16_t runNW = 0;
	uint16_t runS = 0;
	uint16_t runSW = 0;
	uint16_t runW = 0;
	for (auto frame = jsonFile["frames"].begin(); frame != jsonFile["frames"].end(); ++frame) {
		if (frame.key().find("attackN0") != std::string::npos)
			attackN++;
		else if (frame.key().find("attackNW") != std::string::npos)
			attackNW++;
		else if (frame.key().find("attackS0") != std::string::npos)
			attackS++;
		else if (frame.key().find("attackSW") != std::string::npos)
			attackSW++;
		else if (frame.key().find("attackW") != std::string::npos)
			attackW++;
		else if (frame.key().find("dieN0") != std::string::npos)
			dieN++;
		else if (frame.key().find("dieNW") != std::string::npos)
			dieNW++;
		else if (frame.key().find("dieS0") != std::string::npos)
			dieS++;
		else if (frame.key().find("dieSW") != std::string::npos)
			dieSW++;
		else if (frame.key().find("dieW") != std::string::npos)
			dieW++;
		else if (frame.key().find("idleN0") != std::string::npos)
			idleN++;
		else if (frame.key().find("idleNW") != std::string::npos)
			idleNW++;
		else if (frame.key().find("idleS0") != std::string::npos)
			idleS++;
		else if (frame.key().find("idleSW") != std::string::npos)
			idleSW++;
		else if (frame.key().find("idleW") != std::string::npos)
			idleW++;
		else if (frame.key().find("runN0") != std::string::npos)
			runN++;
		else if (frame.key().find("runNW") != std::string::npos)
			runNW++;
		else if (frame.key().find("runS0") != std::string::npos)
			runS++;
		else if (frame.key().find("runSW") != std::string::npos)
			runSW++;
		else if (frame.key().find("runW") != std::string::npos)
			runW++;
		Frame f;
		f.x = frame.value()["frame"]["x"];
		f.y = frame.value()["frame"]["y"];
		f.w = frame.value()["frame"]["w"];
		f.h = frame.value()["frame"]["h"];
		f.rotated = frame.value()["rotated"];
		f.trimmed = frame.value()["trimmed"];
		f.spriteSourceSizeX = frame.value()["spriteSourceSize"]["x"];
		f.spriteSourceSizeY = frame.value()["spriteSourceSize"]["y"];
		f.spriteSourceSizeW = frame.value()["spriteSourceSize"]["w"];
		f.spriteSourceSizeH = frame.value()["spriteSourceSize"]["h"];
		f.sourceSizeW = frame.value()["sourceSize"]["w"];
		f.sourceSizeH = frame.value()["sourceSize"]["h"];
		frames.push_back(f);
	}

	ofstream output_file(fileName+".anim", ios::binary);
	uint32_t size = frames.size();
	output_file.write((char*)&size,sizeof(uint32_t));

	output_file.write((char*)&attackN, sizeof(uint16_t));
	output_file.write((char*)&attackNW, sizeof(uint16_t));
	output_file.write((char*)&attackS, sizeof(uint16_t));
	output_file.write((char*)&attackSW, sizeof(uint16_t));
	output_file.write((char*)&attackW, sizeof(uint16_t));

	output_file.write((char*)&dieN, sizeof(uint16_t));
	output_file.write((char*)&dieNW, sizeof(uint16_t));
	output_file.write((char*)&dieS, sizeof(uint16_t));
	output_file.write((char*)&dieSW, sizeof(uint16_t));
	output_file.write((char*)&dieW, sizeof(uint16_t));

	output_file.write((char*)&idleN, sizeof(uint16_t));
	output_file.write((char*)&idleNW, sizeof(uint16_t));
	output_file.write((char*)&idleS, sizeof(uint16_t));
	output_file.write((char*)&idleSW, sizeof(uint16_t));
	output_file.write((char*)&idleW, sizeof(uint16_t));

	output_file.write((char*)&runN, sizeof(uint16_t));
	output_file.write((char*)&runNW, sizeof(uint16_t));
	output_file.write((char*)&runS, sizeof(uint16_t));
	output_file.write((char*)&runSW, sizeof(uint16_t));
	output_file.write((char*)&runW, sizeof(uint16_t));

	output_file.write((char*)&frames[0], sizeof(Frame)*frames.size());
	output_file.close();
}

JSONToBinary::JSONToBinary()
{
}


JSONToBinary::~JSONToBinary()
{
}
