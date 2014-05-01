#include "TestState.h"
#include "../engine/kWinApp.h"
#include "../engine/kCamera.h"
#include "../engine/kDebugDraw.h"

#include "../engine/kRenderSystem.h"
#include "../engine/kRenderParams.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TestState::TestState( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Desctructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TestState::~TestState( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the current states
Params:
	_app - the pointer to the main application
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TestState::Initialize( kWinApp* _app )
{
	m_App = _app;

	m_DebugCam = new kCamera();
	m_DebugCam->CreateOrthoMatrix( 
		float(m_App->GetWidth()) * 0.5f,
		float(m_App->GetHeight()) * 0.5f,
		0.0f, 1000.0f );

	g_RenderPassDebug.SetCamera( m_DebugCam );

	m_DebugDraw = new kDebugDraw();
	m_DebugDraw->DrawRect(-128.0f,  0.0f, 32.0f, 32.0f, false, D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) );
	m_DebugDraw->DrawRect(   0.0f,-16.0f, 32.0f, 32.0f, true,  D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) );
	m_DebugDraw->DrawRect( 128.0f,  0.0f, 32.0f, 32.0f, false, D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) );

	m_DebugDraw->DrawLine(-128.0f,  64.0f, -64.0f, 128.0f, D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f ) );
	m_DebugDraw->DrawLine( -64.0f, 128.0f,   0.0f,  64.0f, D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f ) );
	m_DebugDraw->DrawLine(   0.0f,  64.0f,  64.0f, 128.0f, D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f ) );
	m_DebugDraw->DrawLine( 128.0f,  64.0f,  64.0f, 128.0f, D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f ) );

	m_DebugDraw->DrawCircle(-128.0f, -96.0f, 32.0f, false, D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f ) );
	m_DebugDraw->DrawCircle(   0.0f,-128.0f, 32.0f, true,  D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f ) );
	m_DebugDraw->DrawCircle( 128.0f, -96.0f, 32.0f, false, D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f ) );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Releases all the data contained by this state
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TestState::Release( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the state and all it contains
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TestState::Update( float _timing )
{
	m_DebugCam->Update( _timing );
	m_DebugDraw->Update( _timing );
}
