#include "stdafx.h"
#include "BMPGenerator.h"
#include <fstream>

CBMPGenerator::CBMPGenerator()
{
}


CBMPGenerator::~CBMPGenerator()
{
}

void CBMPGenerator::SaveBitmap(const char* name, size_t width, size_t height, std::function<C_RGB(int x, int y)> fn) {
	size_t pixelDataSize = width * height;
	std::vector<C_RGB> colors;
	colors.resize(pixelDataSize);
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			colors[i* width + j] = fn(j, i);
		}
	}


	//===== Save File ======
	size_t fileSize = 54 + 3 * pixelDataSize;
	unsigned char fileHeader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char infoHeader[40];
	memset(infoHeader, 0, 40);

	fileHeader[2] = (unsigned char)(fileSize);
	fileHeader[3] = (unsigned char)(fileSize >> 8);
	fileHeader[4] = (unsigned char)(fileSize >> 16);
	fileHeader[5] = (unsigned char)(fileSize >> 24);


	infoHeader[0] = 40;
	infoHeader[4] = (unsigned char)(width);
	infoHeader[5] = (unsigned char)(width >> 8);
	infoHeader[6] = (unsigned char)(width >> 16);
	infoHeader[7] = (unsigned char)(width >> 24);
	infoHeader[8] = (unsigned char)(height);
	infoHeader[9] = (unsigned char)(height >> 8);
	infoHeader[10] = (unsigned char)(height >> 16);
	infoHeader[11] = (unsigned char)(height >> 24);
	infoHeader[14] = 32;


	std::vector<char> imgData;
	imgData.resize(width*height*4);
	for (int i = 0; i < height; i++)
	{
		for (int x = 0; x < width; x++)
		{
			int y = height - 1 - i;
			imgData[(x + i*width) * 4 ] = colors[x + y*width].b;
			imgData[(x + i*width) * 4 + 1] = colors[x + y*width].g;
			imgData[(x + i*width) * 4 + 2] = colors[x + y*width].r;
			imgData[(x + i*width) * 4 + 3] = 0;
		}
	}
	std::ofstream imgFile( std::string(name) + ".bmp", std::ofstream::binary);
	imgFile.write((char*)fileHeader, 14);
	imgFile.write((char*)infoHeader, 40);
	imgFile.write((char*)&imgData[0], imgData.size());
	imgFile.close();
	system((std::string(name) + ".bmp").c_str());
}
