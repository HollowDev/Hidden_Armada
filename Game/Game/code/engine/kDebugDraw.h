#pragma once
#ifndef _DEBUG_DRAW_H_
#define _DEBUG_DRAW_H_

#include "directx9.h"
#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Wrapper to allow for debug rendering
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kRenderObjectDebug;
class kRECT;
class kCircle;
class kCollisionVolume;
class kDebugDraw
{
	vector< kRenderObjectDebug* > m_DrawList;
	
public:
	kDebugDraw( void );
	~kDebugDraw( void );

	void Update( float _timing );
	void ClearDrawList( void );

	void DrawRect( float _posX, float _posY, float _halfWidth, float _halfHeight, bool _solid = false, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	void DrawRect( kRECT* _rect, bool _solid = false, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	void DrawLine( float _startX, float _startY, float _endX, float _endY, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	void DrawCircle( float _posX, float _posY, float _radius, bool _solid = false, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	void DrawCircle( kCircle* _circle, bool _solid = false, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	void DrawCollider( kCollisionVolume* _volume, bool _solid = false, D3DXVECTOR4 _color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
};

#endif