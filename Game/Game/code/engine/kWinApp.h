#pragma once
#ifndef _WIN_APP_H_
#define _WIN_APP_H_

#include "windows.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Wrapper for handling a Windows--well--window!
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kStateSystem;
class kBaseState;
class kTimer;
class kWinApp
{
	HWND			m_HWND;
	HINSTANCE		m_HInstance;
	WINDOWPLACEMENT	m_WP;
	int				m_WindowWidth;
	int				m_WindowHeight;
	bool			m_Active;
	bool			m_IsClosing;

	kStateSystem*	m_StateSystem;
	kTimer*			m_Timer;

	LRESULT CALLBACK WndProc( HWND _hWnd, 
							  UINT _message, 
							  WPARAM _wParam, 
							  LPARAM _lParam );

	void Update( void );
	void Render( void );
public:
	kWinApp( void );
	~kWinApp( void );

	void Initialize( LPCWSTR _title, 
					 HINSTANCE _HInstance, 
					 kBaseState* _startState,
					 int _width, 
					 int _height, 
					 bool _windowed = true );
	void Release( void );
	void Run( void );
	void Close( void );

	static LRESULT CALLBACK StaticWndProc( HWND _hWnd, 
										   UINT _message, 
										   WPARAM _wParam, 
										   LPARAM _lParam );

	inline int GetWidth( void ) const			{ return m_WindowWidth;		}
	inline int GetHeight( void ) const			{ return m_WindowHeight;	}
	inline HWND GetHWND( void ) const			{ return m_HWND;			}
	inline HINSTANCE GetHINSTANCE(void) const	{ return m_HInstance;		}
	inline kStateSystem* GetStateSystem( void ) { return m_StateSystem;		}
};

#endif