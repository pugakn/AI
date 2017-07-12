#include "stdafx.h"
#include "PerlinNoise.h"

#include <algorithm>

void PerlinNoise::Init(int seed, RAND_TYPE randtype)
{
	permutationTable.resize(TABLE_SIZE);
	randomEngine.seed (seed);
	randomNumbers.SetSeed(seed);

	if (randtype == RAND_TYPE::ZIGGURAT)
	{
		randomNumbers.InitZiggurat(seed);

		for (unsigned i = 0; i < TABLE_SIZE; ++i) {
			gradients[i] = Vector3D(2 * randomNumbers.GetZigguratRandomNumber() - 1, 2 * randomNumbers.GetZigguratRandomNumber() - 1, 2 * randomNumbers.GetZigguratRandomNumber() - 1);
			gradients[i] = Normalize(gradients[i]);
			permutationTable[i] = i;
		}
	}
	else {
		for (unsigned i = 0; i < TABLE_SIZE; ++i) {
			auto num = randomNumbers.GetBoxMullerRandomNumber();
			gradients[i] = Vector3D(2 * num.first - 1, 2 * num.second - 1, 2 * randomNumbers.GetBoxMullerRandomNumber().first - 1);
			gradients[i] = Normalize(gradients[i]);
			permutationTable[i] = i;
		}
	}
	std::uniform_int_distribution<int> intDistribution(0, TABLE_SIZE - 1);
	for (unsigned i = 0; i < TABLE_SIZE; ++i)
		std::swap(permutationTable[i], permutationTable[intDistribution(randomEngine)]);
	permutationTable.insert(permutationTable.end(), permutationTable.begin(), permutationTable.end());
}

//void PerlinNoise::AddOctave(Octave octave)
//{
//	octaves.push_back(octave);
//}

double PerlinNoise::PixelValue(double x, double y, double z, double persistence, int octaves)
{
	//double pixelValue = 0;
	//for (auto &octave : octaves)
	//{
	//	pixelValue +=  Perlin(x * octave.frequency, y * octave.frequency, z * octave.frequency) * octave.amplitude;
	//}
	//return pixelValue / octaves.size();
	double total = 0;
	double frequency = 0.8;
	double amplitude = 0.5;
	double maxValue = 0; 
	for (int i = 0; i < octaves; i++) {
		total += Perlin(x * frequency, y * frequency, z * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

double PerlinNoise::Perlin(double x, double y, double z)
{
	int bootomLeftX = ((int)std::floor(x)) &TABLE_MAX_INDEX;
	int bootomLeftY = ((int)std::floor(y)) &TABLE_MAX_INDEX;
	int bootomLeftZ = ((int)std::floor(z)) &TABLE_MAX_INDEX;
	int TopRightX = (bootomLeftX + 1) & TABLE_MAX_INDEX;
	int TopRightY = (bootomLeftY + 1) & TABLE_MAX_INDEX;
	int TopRightZ = (bootomLeftZ + 1) & TABLE_MAX_INDEX;

	x -= ((int)std::floor(x));
	y -= ((int)std::floor(y));
	z -= ((int)std::floor(z));

	float u = fade(x);
	float v = fade(y);
	float w = fade(z);

	Vector3D &c000 = gradients[hash(bootomLeftX, bootomLeftY, bootomLeftZ)];
	Vector3D &c100 = gradients[hash(TopRightX, bootomLeftY, bootomLeftZ)];
	Vector3D &c010 = gradients[hash(bootomLeftX, TopRightY, bootomLeftZ)];
	Vector3D &c110 = gradients[hash(TopRightX, TopRightY, bootomLeftZ)];

	Vector3D &c001 = gradients[hash(bootomLeftX, bootomLeftY, TopRightZ)];
	Vector3D &c101 = gradients[hash(TopRightX, bootomLeftY, TopRightZ)];
	Vector3D &c011 = gradients[hash(bootomLeftX, TopRightY, TopRightZ)];
	Vector3D &c111 = gradients[hash(TopRightX, TopRightY, TopRightZ)];

	float x0 = x, x1 = x - 1;
	float y0 = y, y1 = y - 1;
	float z0 = z, z1 = z - 1;

	Vector3D p000(x0, y0, z0);
	Vector3D p100(x1, y0, z0);
	Vector3D p010(x0, y1, z0);
	Vector3D p110(x1, y1, z0);

	Vector3D p001(x0, y0, z1);
	Vector3D p101(x1, y0, z1);
	Vector3D p011(x0, y1, z1);
	Vector3D p111(x1, y1, z1);

	float a = lerp(Dot(c000, p000), Dot(c100, p100), u);
	float b = lerp(Dot(c010, p010), Dot(c110, p110), u);
	float c = lerp(Dot(c001, p001), Dot(c101, p101), u);
	float d = lerp(Dot(c011, p011), Dot(c111, p111), u);

	float e = lerp(a, b, v);
	float f = lerp(c, d, v);
	return lerp(e, f, w) ;

}

PerlinNoise::PerlinNoise()
{
}


PerlinNoise::~PerlinNoise()
{
}
