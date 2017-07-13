#pragma once

#include <memory>
#include <list>
#include <vector>
#include "FSM\Subject.h"
#include "DungeonMap.h"


#include <memory>
class CWorld;
class FSMMarchingSq;
class Tile;
class CMarchingState
{
protected:
	FSMMarchingSq* m_fsm;
	CWorld* m_pWorld;
public:
	void SetWorlPtr(CWorld* ptr);
	CMarchingState();
	virtual void Update(Tile * tile ) = 0;
	virtual void OnEnter(Tile * tile) = 0;
	virtual void OnExit(Tile * tile) = 0;
	void SetFSM(FSMMarchingSq* fsm);
	virtual ~CMarchingState();
};

class CMarchingSearching : public CMarchingState
{
public:
	void Update(Tile * tile) override;
	void OnEnter(Tile * tile) override;
	void OnExit(Tile * tile) override;
};


class CMarchingDone : public CMarchingState
{
public:
	void Update(Tile * tile) override;
	void OnEnter(Tile * tile) override;
	void OnExit(Tile * tile) override;

};


class FSMMarchingSq 
{

public:
	enum MARCHING_STATES
	{
		DONE,
		SEARCHING
	};
	std::vector<std::shared_ptr<CMarchingState>> m_states; //Lista a de todos los estados disponibles

	void Init(CWorld * world);
	void SetState(Tile *tile, MARCHING_STATES state);
	void Update(float delta);
	void Destroy();
	FSMMarchingSq();
	~FSMMarchingSq();
};



