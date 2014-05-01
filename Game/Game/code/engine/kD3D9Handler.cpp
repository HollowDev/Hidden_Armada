#include "kD3D9Handler.h"
#include "memory_macros.h"

HWND						kD3D9Handler::m_hWnd;
HINSTANCE					kD3D9Handler::m_hInstance;
D3DCAPS9					kD3D9Handler::m_Caps;
D3DPRESENT_PARAMETERS		kD3D9Handler::m_PP;
D3DDISPLAYMODE				kD3D9Handler::m_DisplayMode;
IDirect3D9*					kD3D9Handler::m_Object		= nullptr;
IDirect3DDevice9*			kD3D9Handler::m_Device		= nullptr;
ID3DXSprite*				kD3D9Handler::m_Sprite		= nullptr;
ID3DXLine*					kD3D9Handler::m_Line		= nullptr;
BOOL						kD3D9Handler::m_IsWindowed;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kD3D9Handler::kD3D9Handler( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kD3D9Handler::~kD3D9Handler( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Cleans up resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kD3D9Handler::Release( void )
{
	SAFE_RELEASE( m_Device );
	SAFE_RELEASE( m_Object );
	SAFE_RELEASE( m_Sprite );
	SAFE_RELEASE( m_Line );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Initializes Direct3D.
Params:
	_hWnd - Handle to the window
	_windowed - TRUE for windowed mode, FALSE for fullscreen mode
Returns: 
	BOOL - TRUE on success. FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL kD3D9Handler::Initialize( HWND _hWnd, BOOL _windowed )
{
	m_IsWindowed = _windowed;
	m_hWnd = _hWnd;
	Release();

	// Create the object
	m_Object = Direct3DCreate9(D3D_SDK_VERSION);

	m_Object->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_DisplayMode );
	m_Object->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_Caps );

	if( !BuildPresentParameters() )
	{
		SAFE_RELEASE( m_Object );
		return FALSE;
	}

	// Create the Device
	m_Object->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_PP, &m_Device );
	
	// Create the sprite
	D3DXCreateSprite(m_Device, &m_Sprite);

	// Create the line
	D3DXCreateLine(m_Device, &m_Line);
	m_Line->SetAntialias(TRUE);
	m_Line->SetWidth(1.0f);
	
	return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Builds the D3DPRESENT_PARAMETERS structure.
Returns: 
	BOOL - TRUE on success. FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL kD3D9Handler::BuildPresentParameters( void )
{
	ZeroMemory( &m_PP, sizeof(m_PP) );
	D3DFORMAT adapterFormat = (m_IsWindowed) ? m_DisplayMode.Format : D3DFMT_X8R8G8B8;
    if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D24S8;
    }
    else if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D24X8;
    }
    else if ( SUCCEEDED( m_Object->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
    {
        m_PP.AutoDepthStencilFormat = D3DFMT_D16;
    }
	else
	{
		return FALSE;
	}

	m_PP.BackBufferWidth			= (m_IsWindowed) ? 0 : m_DisplayMode.Width;
	m_PP.BackBufferHeight           = (m_IsWindowed) ? 0 : m_DisplayMode.Height;
	m_PP.BackBufferFormat           = adapterFormat;
	m_PP.BackBufferCount            = 1;
	m_PP.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_PP.MultiSampleQuality         = 0;
	m_PP.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_PP.hDeviceWindow              = m_hWnd;
	m_PP.Windowed                   = m_IsWindowed;
	m_PP.EnableAutoDepthStencil     = TRUE; 
	m_PP.FullScreen_RefreshRateInHz = (m_IsWindowed) ? 0 : m_DisplayMode.RefreshRate;
	m_PP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	return TRUE;
}
