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

	friend class CAttack;
	friend class CMoveTo;
	friend class CRecollect;
	friend class CGuarrison;
	friend class CBuild;
	std::weak_ptr<CUnit> m_target;
	Vector3D m_targetPos;

public:
	unsigned int m_uId;

	//====== TODO: Implementar funciones ======
	bool CanRecolect();
	bool CanBuild();
	bool IsBelic();
	bool IsDead();
	bool TargetIsDead();
	bool TargetIsEnemy();
	bool TargetIsInAttackRange();
	bool IsInGuarrison();
	bool CanAttack();
	bool IsFull();
	bool SeesEnemies();
	bool HasBuildOrders();
	void Build();
	bool BuildCompleted();
	void SearchBuildingUnit();
	bool IsInBuildRange();
	void SetNearestTarget();
	bool ArrivedToTargetPos();
	void Recolect();
	void DepositResources();
	void MoveToNearestResource();
	void IncRotingTime();
	bool Roted();
	bool CanGuarrison();
	void MoveTo(Vector3D poisition);
	void AttackTarget();
	void Reload();
	void GuarrisonOnTarget();
	void TakeDamage(float damage);
	void Die();
	//====================================
	void SetState(std::weak_ptr<CState> state);

	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	CUnit();
	~CUnit();
};

