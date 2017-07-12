// AIBMP_Gen.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "BMPGenerator.h"
#include "RandomNumbers.h"
#include "PerlinNoise.h"
using namespace std;

enum class PixelFunctionID
{
	TEST = 0,
	ZIGGURAT,
	BOXMULLER,
	PERLINNOISE,
	DEFAULT
};

int main(int argc, char* argv[])
{
	CBMPGenerator bmpGen;
	size_t imgWidth = 512;
	size_t imgHeight = 512;
	string imgName = "new";
	size_t seed = 666;
	PixelFunctionID pixelFunction = PixelFunctionID::PERLINNOISE;
	for (size_t i = 0; i < argc; i++)
	{
		if ( string(argv[i]) == "--help") {
			cerr << "-t, --test : \t Use test funtion" <<endl;
			cerr << "-h, --height : \t Defines image height" << endl;
			cerr << "-w, --width : \t Defines image width" << endl;
			cerr << "-n, --name : \t Defines image name" << endl;
			return 0;
		}
		if (string(argv[i]) == "-t" || string(argv[i]) == "--test") {
			pixelFunction = PixelFunctionID::TEST;
		}
		else if (string(argv[i]) == "-b" || string(argv[i]) == "--boxmuller")
			pixelFunction = PixelFunctionID::BOXMULLER;
		else if (string(argv[i]) == "-z" || string(argv[i]) == "--ziggurat")
			pixelFunction = PixelFunctionID::ZIGGURAT;
		else if (string(argv[i]) == "-p" || string(argv[i]) == "--perlin")
			pixelFunction = PixelFunctionID::PERLINNOISE;
		else if (i + 1 < argc) {
			if (string(argv[i]) == "-w" || string(argv[i]) == "--width") {
				imgWidth = atoi(argv[i + 1]);
			}
			else if (string(argv[i]) == "-h" || string(argv[i]) == "--height") {
				imgHeight = atoi(argv[i + 1]);
			}
			else if (string(argv[i]) == "-n" || string(argv[i]) == "--name") {
				imgName = argv[i + 1];
			}
			else if (string(argv[i]) == "-s" || string(argv[i]) == "--see") {
				seed = atoi(argv[i + 1]);
			}
		}
	}
	RandomNumbers randomGen;
	randomGen.SetSeed(seed);
	randomGen.InitZiggurat(256);
	PerlinNoise perlin;
	perlin.Init(seed, PerlinNoise::BOX_MULLER);
	//PerlinNoise::Octave oc;
	//oc.amplitude = 1;
	//oc.frequency = 0.02;
	//perlin.AddOctave(oc);
	//oc.amplitude = 7;
	//oc.frequency = 0.001;
	//perlin.AddOctave(oc);



	cerr << "Generating bitmap..." << endl;
	switch (pixelFunction)
	{
	case PixelFunctionID::TEST:
		bmpGen.SaveBitmap(imgName.c_str(),imgWidth, imgHeight, [](int x, int y)->C_RGB {
			C_RGB pixelColor;
			pixelColor = C_RGB(x%256, y%256, 0);
			return pixelColor;
		});
		cerr << "====BMP SAVED USING TEST!====" << endl;
		break;
	case PixelFunctionID::ZIGGURAT:
		bmpGen.SaveBitmap(imgName.c_str(), imgWidth, imgHeight, [&randomGen](int x, int y)->C_RGB {
			C_RGB pixelColor;
			pixelColor = C_RGB(((int)randomGen.GetZigguratRandomNumber()*50) % 256, ((int)randomGen.GetZigguratRandomNumber()*50) % 256, 0);
			return pixelColor;
		});
		cerr << "====BMP SAVED USING ZIGGURAT!====" << endl;
		break;
	case PixelFunctionID::BOXMULLER:
		bmpGen.SaveBitmap(imgName.c_str(), imgWidth, imgHeight, [&randomGen](int x, int y)->C_RGB {
			C_RGB pixelColor;
			auto a = randomGen.GetBoxMullerRandomNumber();
			pixelColor = C_RGB(((int)a.first * 50) % 256, ((int)a.second * 50) % 256, 0);
			return pixelColor;
		});
		cerr << "====BMP SAVED USING BOXMULLER!====" << endl;
		break;
	case PixelFunctionID::PERLINNOISE:
		bmpGen.SaveBitmap(imgName.c_str(), imgWidth, imgHeight, [&perlin](int x, int y)->C_RGB {
			C_RGB pixelColor;
			auto a = (perlin.PixelValue(x/20.0,y/20.0,0.0,0.8,8) + 1) /2.0 * 255;
			pixelColor = C_RGB(a, a, a);
			return pixelColor;
		});
		cerr << "====BMP SAVED USING PERLIN NOISE!====" << endl;
		break;
	default:
		break;
	}
	cerr << "| HEIGHT: " << imgHeight << endl;
	cerr << "| WIDTH: " << imgWidth << endl;
	cerr << "| NAME: " << imgName << endl;


	////=============
	//RandomNumbers randomGen;
	//randomGen.SetSeed(222);
	//for (size_t i = 0; i < 10; i++)
	//{
	//	cout << randomGen.GetBoxMullerRandomNumber().first << "   "  << randomGen.GetBoxMullerRandomNumber().second << endl;
	//}
	//cout << endl  <<endl <<endl;
	////===========
	//randomGen.InitZiggurat(128);
	//for (size_t i = 0; i < 10; i++)
	//{
	//	cout << randomGen.GetZigguratRandomNumber() << endl;
	//}
    return 0;
}



