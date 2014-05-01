#include "kCamera.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCamera::kCamera( void )
{
	D3DXMatrixIdentity( &m_View );
	D3DXMatrixIdentity( &m_Proj );
	D3DXMatrixIdentity( &m_ViewProj );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCamera::~kCamera( void )
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructs an orthographic projection matrix
Params:
	_halfWidth - half the screen width
	_halfHeight - half the screen height
	_near - value for the near plane
	_far - value for the far plane
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCamera::CreateOrthoMatrix( 
	float _halfWidth, 
	float _halfHeight, 
	float _near, 
	float _far 
	)
{
	D3DXMatrixOrthoOffCenterLH( 
		&m_Proj, 
		-_halfWidth, 
		_halfWidth, 
		-_halfHeight, 
		_halfHeight, 
		_near, 
		_far 
		);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the camera, by calculating the m_ViewProj matrix.
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCamera::Update( float _timing )
{
	m_ViewProj = m_View * m_Proj;
}
