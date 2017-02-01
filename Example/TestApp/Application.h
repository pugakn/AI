#include <Core.h>

#include <d3dx9math.h>
#include <Timer.h>

#include "World.h"

class TestApp : public AppBase {
private:
	CWorld m_World;
public:
	TestApp() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();

	D3DXVECTOR3		Scaling;

	D3DXMATRIX		View;
	D3DXMATRIX		Projection;
	D3DXMATRIX		VP;

	Timer			DtTimer;
};