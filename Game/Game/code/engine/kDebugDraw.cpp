#include "kDebugDraw.h"
#include "kRenderObjectDebug.h"

#include "memory_macros.h"
#include "kVertexBuffer.h"
#include "kIndexBuffer.h"
#include "kRenderParams.h"

#include "kCollisionVolumes.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kDebugDraw::kDebugDraw( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kDebugDraw::~kDebugDraw( void )
{
	ClearDrawList();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the debug draw list
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::Update( float _timing )
{
}
	
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Clears all of the objects from the g_DebugRenderPass
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::ClearDrawList( void )
{
	for( unsigned int i = 0; i < m_DrawList.size(); ++i )
	{
		g_RenderPassDebug.RemoveRenderObject( m_DrawList[i] );
		SAFE_DELETE( m_DrawList[i] );
	}
	m_DrawList.clear();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Construct a debug rect to draw using g_RenderPassDebug
Params:
	_posX - the position of the rect on the X axis
	_posY - the position of the rect on the Y axis
	_halfWidth - half of the width of the rect
	_halfHeight - half of the height of the rect
	_solid - should this be made of lines or be filled?
	_color - the color to render this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::DrawRect( float _posX, float _posY, float _halfWidth, float _halfHeight, bool _solid, D3DXVECTOR4 _color )
{
	// Initialize the buffers
	kRenderObjectDebug* debugDraw = new kRenderObjectDebug();
	kVertexBuffer<kVertex_Pos>* vertexBuffer = new kVertexBuffer<kVertex_Pos>();
	kIndexBuffer* indexBuffer = new kIndexBuffer();
	
	// Construct the vertex buffer and index buffer
	if( !_solid )
	{
		kVertex_Pos* verts = vertexBuffer->Lock( 4 );
		unsigned int* indices = indexBuffer->Lock( 8 );
		{
			verts[0] = kVertex_Pos( _posX - _halfWidth,	_posY + _halfHeight,	0.0f );	//	 0 ---- 1
			verts[1] = kVertex_Pos( _posX + _halfWidth,	_posY + _halfHeight,	0.0f );	//	 |	 /	|
			verts[2] = kVertex_Pos( _posX - _halfWidth,	_posY - _halfHeight,	0.0f );	//	 |  /	|
			verts[3] = kVertex_Pos( _posX + _halfWidth,	_posY - _halfHeight,	0.0f );	//	 2 ---- 3

			indices[0] = 0; indices[1] = 1; 
			indices[2] = 1; indices[3] = 3;
			indices[4] = 3; indices[5] = 2;
			indices[6] = 2; indices[7] = 0;
		}
		vertexBuffer->Unlock();
		indexBuffer->Unlock();
	}
	else
	{
		kVertex_Pos* verts = vertexBuffer->Lock( 4 );
		unsigned int* indices = indexBuffer->Lock( 6 );
		{
			verts[0] = kVertex_Pos( _posX - _halfWidth,	_posY + _halfHeight,	0.0f );	//	 0 ---- 1
			verts[1] = kVertex_Pos( _posX + _halfWidth,	_posY + _halfHeight,	0.0f );	//	 |	 /	|
			verts[2] = kVertex_Pos( _posX - _halfWidth,	_posY - _halfHeight,	0.0f );	//	 |  /	|
			verts[3] = kVertex_Pos( _posX + _halfWidth,	_posY - _halfHeight,	0.0f );	//	 2 ---- 3

			indices[0] = 0; indices[1] = 1; indices[2] = 2;
			indices[3] = 1; indices[4] = 3; indices[5] = 2;
		}
		vertexBuffer->Unlock();
		indexBuffer->Unlock();

		debugDraw->SetPrimitiveType( D3DPT_TRIANGLELIST );
	}
	
	debugDraw->SetVertexBuffer( vertexBuffer );
	debugDraw->SetIndexBuffer( indexBuffer );
	debugDraw->SetRenderColor( _color );

	m_DrawList.push_back( debugDraw );
	g_RenderPassDebug.AddRenderObject( debugDraw );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Construct a debug rect to draw using g_RenderPassDebug
Params:
	_rect - the rect to draw
	_solid - should this be made of lines or be filled?
	_color - the color to render this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::DrawRect( kRECT* _rect, bool _solid, D3DXVECTOR4 _color )
{
	DrawRect( _rect->GetPos().x, _rect->GetPos().y, _rect->m_HalfWidth, _rect->m_HalfHeight, _solid, _color );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Construct a debug line to draw using g_RenderPassDebug
Params:
	_startX - the starting pos of the line on the X axis
	_startY - the starting pos of the line on the Y axis
	_endX - the ending pos of the line on the X axis
	_endY - the ending pos of the line on the Y axis
	_color - the color to render this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::DrawLine( float _startX, float _startY, float _endX, float _endY, D3DXVECTOR4 _color )
{
	// Initialize the buffers
	kVertexBuffer<kVertex_Pos>* vertexBuffer = new kVertexBuffer<kVertex_Pos>();
	kIndexBuffer* indexBuffer = new kIndexBuffer();
	
	// Construct the vertex buffer and index buffer
	kVertex_Pos* verts = vertexBuffer->Lock( 2 );
	unsigned int* indices = indexBuffer->Lock( 2 );
	{
		//	 0 ---- 1
		verts[0] = kVertex_Pos( _startX, _startY, 0.0f );
		verts[1] = kVertex_Pos( _endX, _endY, 0.0f );

		indices[0] = 0; indices[1] = 1; 
	}
	vertexBuffer->Unlock();
	indexBuffer->Unlock();
	
	kRenderObjectDebug* debugDraw = new kRenderObjectDebug();
	debugDraw->SetVertexBuffer( vertexBuffer );
	debugDraw->SetIndexBuffer( indexBuffer );
	debugDraw->SetRenderColor( _color );

	m_DrawList.push_back( debugDraw );
	g_RenderPassDebug.AddRenderObject( debugDraw );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Construct a debug circle to draw using g_RenderPassDebug
Params:
	_startX - the starting pos of the circle on the X axis
	_startY - the starting pos of the circle on the Y axis
	_radius - the radius of the circle
	_solid - should this be made of lines or be filled?
	_color - the color to render this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::DrawCircle( float _posX, float _posY, float _radius, bool _solid, D3DXVECTOR4 _color )
{
	int num_segments = int( _radius / 3.0f );
	if( num_segments < 12 ) num_segments = 12;

	// Initialize the buffers
	kRenderObjectDebug* debugDraw = new kRenderObjectDebug();
	kVertexBuffer<kVertex_Pos>* vertexBuffer = new kVertexBuffer<kVertex_Pos>();
	kIndexBuffer* indexBuffer = new kIndexBuffer();
	
	// Construct the vertex buffer and index buffer
	if( !_solid )
	{
		kVertex_Pos* verts = vertexBuffer->Lock( num_segments*2 );
		unsigned int* indices = indexBuffer->Lock( num_segments*2 );
		{
			for( int i = 0; i < num_segments; ++i ) 
			{
				int index = i*2;

				float const t1 = 2.0f * float(D3DX_PI) * (float)i / (float)num_segments;
				float const t2 = 2.0f * float(D3DX_PI) * (float)(i+1) / (float)num_segments;
				verts[index]   = kVertex_Pos( sin(t1) * _radius + _posX, cos(t1) * _radius + _posY, 0.0f );
				verts[index+1] = kVertex_Pos( sin(t2) * _radius + _posX, cos(t2) * _radius + _posY, 0.0f );
				indices[index] = index;
				indices[index+1] = index+1;
			}
		}
		vertexBuffer->Unlock();
		indexBuffer->Unlock();
	}
	else
	{
		kVertex_Pos* verts = vertexBuffer->Lock( num_segments*3 );
		unsigned int* indices = indexBuffer->Lock( num_segments*3 );
		{
			for( int i = 0; i < num_segments; ++i ) 
			{
				int index = i*3;

				float const t1 = 2.0f * float(D3DX_PI) * (float)i / (float)num_segments;
				float const t2 = 2.0f * float(D3DX_PI) * (float)(i+1) / (float)num_segments;
				verts[index]   = kVertex_Pos( sin(t1) * _radius + _posX, cos(t1) * _radius + _posY, 0.0f );
				verts[index+1] = kVertex_Pos( sin(t2) * _radius + _posX, cos(t2) * _radius + _posY, 0.0f );
				verts[index+2] = kVertex_Pos( _posX, _posY, 0.0f );
				indices[index] = index;
				indices[index+1] = index+1;
				indices[index+2] = index+2;
			}
		}
		vertexBuffer->Unlock();
		indexBuffer->Unlock();

		debugDraw->SetPrimitiveType( D3DPT_TRIANGLELIST );
	}
	
	debugDraw->SetVertexBuffer( vertexBuffer );
	debugDraw->SetIndexBuffer( indexBuffer );
	debugDraw->SetRenderColor( _color );

	m_DrawList.push_back( debugDraw );
	g_RenderPassDebug.AddRenderObject( debugDraw );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Construct a debug circle to draw using g_RenderPassDebug
Params:
	_circle - the circle to create the debug info off of
	_solid - should this be made of lines or be filled?
	_color - the color to render this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kDebugDraw::DrawCircle( kCircle* _circle, bool _solid, D3DXVECTOR4 _color )
{
	DrawCircle( _circle->GetPos().x, _circle->GetPos().y, _circle->m_Radius, _solid, _color );
}
	
void kDebugDraw::DrawCollider( kCollisionVolume* _volume, bool _solid, D3DXVECTOR4 _color )
{
	if( _volume->GetType() == Type_RECT )
		DrawRect( (kRECT*)_volume, _solid, _color );
	else if( _volume->GetType() == Type_Circle )
		DrawCircle( (kCircle*)_volume, _solid, _color );
}