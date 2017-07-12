#include "stdafx.h"
#include "RandomNumbers.h"
#include <math.h>
void RandomNumbers::SetSeed(int s)
{
	seed = s;
	randomEngine.seed(seed);
}

std::pair<float, float> RandomNumbers::GetBoxMullerRandomNumber()
{
	static const std::uniform_real_distribution<float> uDist(-1, 1);
	float u ;
	float v ;
	float r ;
	while (true)
	{
		u = uDist(randomEngine);
		v = uDist(randomEngine);
		r = u*u + v*v;
		if (r < 1 && r > 0)
			break;
	}
	r = sqrt((-2.0 *  log(r)) / r);
	u = abs(u * r);
	v = abs(v * r);
	return std::pair<float, float>(u,v);
}

float RandomNumbers::GetZigguratRandomNumber()
{
	static const std::uniform_real_distribution<float> uDist(0, 1);
	while (true)
	{
		int index = 1 + (rand() % zigguratBlocks);
		float u0 = uDist(randomEngine);
		float x = u0*index;
		if (x < index - 1 &&  index != 0)
			return x;//Inside block
		if (index == zigguratBlocks)
			continue;//return x;//from tail
		float u1 = uDist(randomEngine);
		float y = u1 * (zigguratFx[index - 1] - zigguratFx[index]);
		if (y < ((1.0 / (sqrtf(2 * M_PI))) * exp((x*x)*-0.5) - zigguratFx[index]))
			return x;
	}
}

void RandomNumbers::InitZiggurat(int blocks)
{
	zigguratBlocks = blocks;
	zigguratFx.clear();
	for (size_t i = 0; i <= zigguratBlocks; i++)
	{
		zigguratFx.push_back((1.0/ (sqrtf(2 * M_PI))) * exp((i*i)*-0.5));
	}
}

RandomNumbers::RandomNumbers()
{
}


RandomNumbers::~RandomNumbers()
{
}
