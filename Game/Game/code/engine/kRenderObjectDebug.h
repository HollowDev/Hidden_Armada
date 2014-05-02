#pragma once
#ifndef _RENDER_OBJECT_DEBUG_H_
#define _RENDER_OBJECT_DEBUG_H_

#include "kRenderObject.h"
#include "kVertexBuffer.h"
#include "kVertexFormat.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: kRenderObject used to render debug lines and meshes.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kIndexBuffer;
class kRenderObjectDebug : public kRenderObject
{
	kVertexBuffer<kVertex_Pos>*	 m_VertexBuffer;
	kIndexBuffer*	 m_IndexBuffer;
	D3DXVECTOR4		 m_RenderColor;
	D3DPRIMITIVETYPE m_PrimitiveType;

public:
	kRenderObjectDebug( void );
	~kRenderObjectDebug( void );

	virtual void Render( kRenderPass* _renderPass, ID3DXEffect* _effect );

	// Accessors
	inline kVertexBuffer<kVertex_Pos>* GetVertexBuffer( void )	{ return m_VertexBuffer;	}
	inline kIndexBuffer* GetIndexBuffer( void )					{ return m_IndexBuffer;		}
	inline D3DXVECTOR4 GetRenderColor( void )					{ return m_RenderColor;		}
	inline D3DPRIMITIVETYPE GetPrimitiveType( void )			{ return m_PrimitiveType;	}

	// Mutators
	inline void SetVertexBuffer( kVertexBuffer<kVertex_Pos>* _vertexBuffer )	{ m_VertexBuffer = _vertexBuffer;	}
	inline void SetIndexBuffer( kIndexBuffer* _indexBuffer )					{ m_IndexBuffer = _indexBuffer;		}
	inline void SetRenderColor( D3DXVECTOR4 _renderColor )						{ m_RenderColor = _renderColor;		}
	inline void SetPrimitiveType( D3DPRIMITIVETYPE _primitiveType )				{ m_PrimitiveType = _primitiveType; }
};

#endif