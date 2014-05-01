#include <Windows.h>
#include <random>
#include <ctime>

#include "engine\kWinApp.h"
#include "src\TestState.h"

#define WINDOW_WIDTH	512
#define WINDOW_HEIGHT	512


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Application entry point
Params:
	_hInstance - Application instance
	_hPrevInstance - Junk
	_lpCmdLine - Command line arguments
	_nCmdShow - Window display flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _showCmd)
{
	srand( unsigned int( time( 0 ) ) );
	rand();

	kWinApp app;
#ifdef _DEBUG
	app.Initialize( L"Hidden Armada : DEBUG", _hInstance, new TestState(), WINDOW_WIDTH, WINDOW_HEIGHT );
#else
	app.Initialize( L"Hidden Armada", _hInstance, new TestState(), WINDOW_WIDTH, WINDOW_HEIGHT );
#endif

	app.Run();
	app.Release();

	return 0;
}