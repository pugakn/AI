#pragma once
class CWeaponType
{
private:
	float m_fAttackRangeMax;
	float m_fAttackRangeMin;
	float m_fDamage;
	char m_terrainTypeFlags;
	bool m_bSplashDamage;
	float m_fReloadTime;

public:
	unsigned int m_uId;
	CWeaponType();
	~CWeaponType();
};

