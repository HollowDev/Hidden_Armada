#pragma once
#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

#include "directx9.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: The root of ANY AND ALL renderable objects
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kRenderPass;
class kRenderObject
{
protected:
	D3DXMATRIX m_WorldMat;
public:
	virtual ~kRenderObject( void ) = 0 {}
	virtual void Render( kRenderPass* _renderPass, ID3DXEffect* _effect ) = 0;

	inline D3DXMATRIX GetWorldMat( void ) const		{ return m_WorldMat;		}
	inline void SetWorldMat( D3DXMATRIX _worldMat ) { m_WorldMat = _worldMat;	}
};

#endif