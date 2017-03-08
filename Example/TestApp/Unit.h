#pragma once
#include "Vector3D.h"

#include "GameObject.h"
#include <memory>
#include <vector>
#include "Type.h"
class CFaction;
class CState;
class CUnit : CGameObject
{
private:
	unsigned int m_uIdType;
	unsigned int m_uIdFaction;
	Vector3D m_vDirection;
	float m_fHP;
	std::weak_ptr<CState> m_state;
	std::vector<CUnit> m_queueConstruction;
	std::vector<CUnit> m_guarrisonList;
	std::vector<float> m_reloadTimes;
	float m_fRotingTimer;

public:
	unsigned int m_uId;
	bool CanRecolect();
	bool CanBuild();
	bool IsBelic();
	bool IsDead();
	//bool IsEnemy();
	//bool IsInAttackRange();
	//bool IsVisible();
	//bool CanAttack();
	//bool SeesEnemies();

	void MoveTo(Vector3D poisition);
	void Attack(CUnit unit);
	void Reload();
	void BuildUnit(CUnit unit);
	void Guarrison(CUnit unit);
	void TakeDamage(float damage);
	void Die();

	void SetState(std::weak_ptr<CState> state);

	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	CUnit();
	~CUnit();
};

