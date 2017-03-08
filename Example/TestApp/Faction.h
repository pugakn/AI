#pragma once
#include <vector>
class CFaction
{
private:
	friend class CUnit;

	char m_alliesFlags;
	float m_fResources;
	float m_fModifiers;
	unsigned int m_uMaxPopulation;
public:
	unsigned int m_uId;
	CFaction();
	~CFaction();
};

