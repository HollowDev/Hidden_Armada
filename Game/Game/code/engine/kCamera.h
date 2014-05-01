#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "directx9.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Base camera class in the engine. Holds the matrices needed by any camera.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kCamera
{
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
	D3DXMATRIX m_ViewProj;
public:
	kCamera( void );
	~kCamera( void );

	virtual void CreateOrthoMatrix( float _halfWidth, 
								 float _halfHeight, 
								 float _near, 
								 float _far );
	virtual void Update( float _timing );

	// Accessors
	inline D3DXMATRIX GetView( void ) const		{ return m_View;		}
	inline D3DXMATRIX GetProj( void ) const		{ return m_Proj;		}
	inline D3DXMATRIX GetViewProj( void ) const { return m_ViewProj;	}

	// Mutators
	inline void SetView( D3DXMATRIX _view ) { m_View = _view; }
	inline void SetProj( D3DXMATRIX _proj ) { m_Proj = _proj; }
};

#endif