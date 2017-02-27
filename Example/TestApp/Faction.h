#pragma once
#include <vector>
#include "Unit.h"
namespace Factions {
	enum E
	{
		Red = 0,
		Blue = 2,
		Green = 4,
	};
}
class CFaction
{
private:
	friend class CUnit;

	unsigned int m_uId;
	char m_alliesFlags;
	std::vector<CUnit> m_group;
	float m_fResources;
	float m_fModifiers;
	unsigned int m_uMaxPopulation;
public:
	CFaction();
	~CFaction();
};

