#include "stdafx.h"
#include "Utils.h"
#include <random>

float FloatRand(float min, float max)
{
	return ((max - min)*(static_cast<float>(rand()) / RAND_MAX)) + min;
}