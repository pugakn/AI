#pragma once
#include <vector>
#include "WeaponType.h"
#include "Armor.h"
class CType
{
private:
	friend class CUnit;

	float m_fVisionRange;
	bool m_bCanRecolect;
	bool m_bCanBuild;
	bool m_bisBelic;
	float m_fMaxSpeed;
	std::vector<CWeaponType> m_weapons;
	unsigned int m_uTerrainType;
	std::vector<CArmor> m_armors;
	unsigned int m_uProductionCost;
	bool m_bCanGuarrison;
	bool m_bCanGroup;
	unsigned int m_uMaxGuarrison;
	//Stands
	float m_fConstructionTime;
	unsigned int m_uMaxOrders;
	std::vector<unsigned int> m_constructionTypes;
	float m_fRotingTime;

public:
	unsigned int m_uId;
	CType();
	~CType();
};

