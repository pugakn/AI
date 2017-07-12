#pragma once
#include <tuple>
#include <vector>
#include <random>
const float M_PI = 3.141592;
class RandomNumbers
{
private:
	int seed;
	int zigguratBlocks = 8;
	std::vector<float> zigguratFx;
	std::default_random_engine randomEngine;
public:
	void SetSeed(int s);
	std::pair<float,float> GetBoxMullerRandomNumber();
	float GetZigguratRandomNumber();
	void InitZiggurat(int blocks);
	RandomNumbers();
	~RandomNumbers();
};

