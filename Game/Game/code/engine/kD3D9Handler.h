#pragma once
#ifndef _D3D9_HANDLER_H_
#define _D3D9_HANDLER_H_

#include "directx9.h"

class kD3D9Handler
{
public:
	static HWND						m_hWnd;
	static HINSTANCE				m_hInstance;
	static D3DCAPS9					m_Caps;
	static D3DPRESENT_PARAMETERS	m_PP;
	static D3DDISPLAYMODE			m_DisplayMode;
	static IDirect3D9*				m_Object;
	static IDirect3DDevice9*		m_Device;
	static ID3DXSprite*				m_Sprite;
	static ID3DXLine*				m_Line;
	static BOOL						m_IsWindowed;

	kD3D9Handler( void );
	~kD3D9Handler( void );
	static BOOL Initialize( HWND _hWnd, BOOL _windowed );
	static void Release( void );
	static BOOL BuildPresentParameters( void );
};

#endif