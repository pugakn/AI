#pragma once
#include "Unit.h"
#include "State.h"
#include <memory>
#include <list>
#include <vector>
#include "Subject.h"
namespace States
{
	enum E
	{
		IDLE,
		MOVE_TO,
		ATTACK,
		DEAD,
		ROTING,
		RECOLLECT,
		BUILD,
		GUARRISON
	};
}
class CFSM : public CSubject //Hereda de Subject para implementar el patron de diseño observador
{
public:
	std::vector<std::shared_ptr<CState>> m_states; //Lista a de todos los estados disponibles

	void Init(CWorld * world);
	void SetState(std::weak_ptr<CUnit> unit, std::weak_ptr<CState> state);
	void Update(float delta);
	void Destroy();
	CFSM();
	~CFSM();
};

