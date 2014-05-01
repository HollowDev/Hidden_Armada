#include "kWinApp.h"
#include "kStateSystem.h"
#include "kTimer.h"

#include "kBaseState.h"
#include "kD3D9Handler.h"
#include "kRenderParams.h"
#include "kRenderSystem.h"
#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kWinApp::kWinApp( void )
{
	m_HWND			= NULL;
	m_HInstance		= NULL;
	m_WindowWidth	= -1;
	m_WindowHeight	= -1;
	m_Active		= false;
	m_IsClosing		= false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kWinApp::~kWinApp( void )
{
	Release();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Initializes the window
Params:
	_title - the title to give the window
	_HInstance - handle to the window instance windows has let us use
	_startState - the state to start the game in
	_width - the width of the window
	_height - the height of the window
	_windowed - display the screen as windowed or fullscreen?
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Initialize( 
	LPCWSTR _title, 
	HINSTANCE _HInstance, 
	kBaseState* _startState, 
	int _width, 
	int _height, 
	bool _windowed 
	)
{
	m_HInstance = _HInstance;
	m_WindowWidth = _width;
	m_WindowHeight = _height;
	m_Active = true;

	// Define the window
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)kWinApp::StaticWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_HInstance;
	wcex.hIcon			= LoadIcon(0,IDC_ICON);
	wcex.hCursor		= LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= _title;
	wcex.hIconSm		= 0;

	// Reguster the window
	RegisterClassEx(&wcex);

	// Create the window
	m_HWND = CreateWindow(_title, _title, (_windowed ? WS_OVERLAPPEDWINDOW : WS_POPUP), CW_USEDEFAULT,
		0, m_WindowWidth, m_WindowHeight, 0, 0, m_HInstance, this);

	// Adjust to desired size
	RECT rect = {0, 0, m_WindowWidth, m_WindowHeight};
	AdjustWindowRect(&rect, GetWindowLong(m_HWND, GWL_STYLE), FALSE);
	SetWindowPos(m_HWND, HWND_TOP, 0, 0, rect.right-rect.left, rect.bottom-rect.top,
				 SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);

	// Save current location/size
	ZeroMemory(&m_WP, sizeof(WINDOWPLACEMENT));
	m_WP.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(m_HWND, &m_WP);

	// TODO:: Initialize handlers
	kD3D9Handler::Initialize(m_HWND, _windowed);
	kRenderParams::InitRenderPasses();
	g_RenderSystem.Initialize();
	
	m_StateSystem = new kStateSystem();
	m_StateSystem->Initialize(this,_startState);

	m_Timer = new kTimer();
	m_Timer->Initialize();
	m_Timer->Reset();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Releases all data inside of this class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Release( void )
{
	m_IsClosing = true;
	
	SAFE_DELETE(m_Timer);
	SAFE_DELETE(m_StateSystem);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Runs the window and the game
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Run( void )
{
	MSG msg;
	while(m_Active)
	{
		// Did we recieve a message, or are we idling?
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Advance Game Frame
			this->Update();
			this->Render();
		}
	}
}
	
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Closes the window and the game
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Close( void )
{
	m_Active = false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the game
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Update( void )
{
	static float accumulator = 0.0f;

	m_Timer->Update();

	float deltaTime = m_Timer->GetDeltaTime();
	if(deltaTime > 0.25f)
		deltaTime = 0.25f;
	
	m_StateSystem->Update(deltaTime);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Renders teh game world
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kWinApp::Render( void )
{
	if( !m_Active )
		return;

	g_RenderSystem.Render();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Needed func for processing windows messages
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LRESULT CALLBACK kWinApp::StaticWndProc( 
	HWND _hWnd, 
	UINT _message, 
	WPARAM _wParam, 
	LPARAM _lParam 
	)
{
	if(_message == WM_CREATE)
        SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)_lParam)->lpCreateParams);

    kWinApp *targetApp = (kWinApp*)GetWindowLongPtr(_hWnd,GWLP_USERDATA);

    if(targetApp)
        return targetApp->WndProc(_hWnd, _message, _wParam, _lParam);

    return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Needed func for processing windows messages
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LRESULT CALLBACK kWinApp::WndProc( 
	HWND _hWnd,
	UINT _message, 
	WPARAM _wParam, 
	LPARAM _lParam 
	)
{
	switch(_message)
	{
	case WM_DESTROY:
		{
			m_Active = false;
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		{
			ValidateRect(_hWnd, 0);
		}
		break;
	}
	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}
