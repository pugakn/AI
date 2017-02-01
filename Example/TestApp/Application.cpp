#include "Application.h"

void TestApp::InitVars() {
	DtTimer.Init();
	Scaling		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_World.Init();
}

void TestApp::CreateAssets() {	

}

void TestApp::DestroyAssets() {
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	OnInput();

	m_World.Update(DtTimer.GetDTSecs());

	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	
	m_World.Render();

	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}