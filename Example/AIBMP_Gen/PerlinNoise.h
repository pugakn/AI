#pragma once
#include "Vector3D.h"
#include <vector>
#include <random>
#include "RandomNumbers.h"
class PerlinNoise
{
public:
	enum RAND_TYPE
	{
		ZIGGURAT,
		BOX_MULLER
	};
	struct Octave {
		double amplitude;
		double frequency;
	};
private:
	RandomNumbers randomNumbers;
	static const int TABLE_SIZE = 256;
	static const int TABLE_MAX_INDEX = TABLE_SIZE - 1;
	std::vector<int> permutationTable;
	std::mt19937 randomEngine;
	Vector3D gradients[TABLE_SIZE];
	int hash(const int &x, const int &y, const int &z) const{ return permutationTable[permutationTable[permutationTable[x] + y] + z]; }
	double fade(const double &t) const{ return t * t * t * (t * (t * 6 - 15) + 10); }
	double lerp(const double &a, const double &b, const double &f){ return a + f * (b - a);}
	
	//std::vector<Octave> octaves;
public:
	void Init(int seed, RAND_TYPE randtype);
	//void AddOctave(Octave octave);
	double PixelValue(double x, double y, double z , double persistence, int octaves);
	double Perlin(double x, double y, double z = 0.0);
	PerlinNoise();
	~PerlinNoise();
};

