#pragma once
#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

// TODO:: MAKE THIS SYSTEM TEMPLATED SO IT CAN USE ANY TYPE OF VERTEX
#include "kD3D9Handler.h"
#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Wrapper for a DirectX9 vertex buffer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
class kVertexBuffer
{
	IDirect3DVertexBuffer9*			m_Buffer;
	IDirect3DVertexDeclaration9*	m_Decl;
	VERTEX*							m_Verts;
	unsigned int					m_NumVerts;

public:
	kVertexBuffer( void );
	~kVertexBuffer( void );
	
	VERTEX* Lock( unsigned int _numVerts );
	bool Unlock( void );
	void CreateVertexDecl( void );

	// Accessors
	inline IDirect3DVertexBuffer9* GetBuffer( void )	{ return m_Buffer;		}
	inline IDirect3DVertexDeclaration9* GetDecl( void )	{ return m_Decl;		}
	inline VERTEX* GetVerts( void )						{ return m_Verts;		}
	inline unsigned int GetNumVerts( void )				{ return m_NumVerts;	}
	// Mutators
	inline void SetBuffer( IDirect3DVertexBuffer9* _buffer )	{ m_Buffer = _buffer;		}
	inline void SetDecl( IDirect3DVertexDeclaration9* _decl )	{ m_Decl = _decl;			}
	inline void SetVerts( VERTEX* _verts )						{ m_Verts = _verts;			}
	inline void SetNumVerts( unsigned int _numVerts )			{ m_NumVerts = _numVerts;	}
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
kVertexBuffer<VERTEX>::kVertexBuffer( void )
{
	m_Buffer	= nullptr;
	m_Decl		= nullptr;
	m_Verts		= nullptr;
	m_NumVerts	= 0;

	CreateVertexDecl();
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
kVertexBuffer<VERTEX>::~kVertexBuffer( void )
{
	SAFE_DELETE( m_Verts );
	SAFE_RELEASE( m_Decl );
	SAFE_RELEASE( m_Buffer );
	m_NumVerts = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Locks the vertex buffer so you can construct the new verts
Params:
	_numVerts - the number of verts you will be needing
Return:
	Vertex_PosTex* - Pointer to the verts
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
VERTEX* kVertexBuffer<VERTEX>::Lock( unsigned int _numVerts )
{
	if( m_Verts ) SAFE_DELETE( m_Verts );

	m_NumVerts = _numVerts;
	m_Verts = new VERTEX[m_NumVerts];
	return m_Verts;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Create the vertex buffer.
Return:
	bool - True if successfully built else false.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
bool kVertexBuffer<VERTEX>::Unlock( void )
{
	if( !m_Verts || m_NumVerts == 0 ) return false;

	// Create vertex buffer
	HRESULT hr = kD3D9Handler::m_Device->CreateVertexBuffer( sizeof(VERTEX) * m_NumVerts, 0, 0, D3DPOOL_MANAGED, &m_Buffer, NULL );
	if( FAILED( hr ) ) return false;

	void *vram = 0;
	hr = m_Buffer->Lock( 0, 0, &vram, 0 );
	if( FAILED( hr ) ) return false;
	{
		memcpy( vram, m_Verts, sizeof(VERTEX) * m_NumVerts );
	}
	m_Buffer->Unlock();
	if( FAILED( hr ) ) return false;
	
	return true;
}

#endif