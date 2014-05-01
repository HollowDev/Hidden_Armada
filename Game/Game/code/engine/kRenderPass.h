#pragma once
#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "directx9.h"
#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Description: Render pass contains the information needed for rendering. Camera, shader
			 and any other custom data needed for that render pass.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kRenderObject;
class kCamera;
class kRenderPass
{
	ID3DXEffect*	m_Effect;
	kCamera*		m_Camera;
	vector<kRenderObject*> m_RenderObjects;
public:
	kRenderPass( void );
	~kRenderPass( void );

	virtual void Initialize( LPCWSTR _effectFilePath );
	virtual void Render( void );
	virtual void AddRenderObject( kRenderObject* _renderObject );
	virtual void RemoveRenderObject( kRenderObject* _renderObject );

	// Accessors
	inline ID3DXEffect* GetEffect( void ) const { return m_Effect; }
	inline kCamera* GetCamera( void ) const		{ return m_Camera; }

	// Mutators
	inline void SetEffect( ID3DXEffect* _effect )	{ m_Effect = _effect; }
	inline void SetCamera( kCamera* _camera )		{ m_Camera = _camera; }
};

#endif