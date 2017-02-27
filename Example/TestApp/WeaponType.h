#pragma once
namespace Terrains {
	enum E
	{
		Ground = 0,
		Air = 2,
		Sea = 4,
	};
}
class CWeaponType
{
private:
	unsigned int m_uId;
	float m_fAttackRangeMax;
	float m_fAttackRangeMin;
	float m_fDamage;
	char m_terrainTypeFlags;
	bool m_bSplashDamage;
	float m_fReloadTime;

public:
	CWeaponType();
	~CWeaponType();
};

