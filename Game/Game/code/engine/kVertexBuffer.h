#pragma once
#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

// TODO:: MAKE THIS SYSTEM TEMPLATED SO IT CAN USE ANY TYPE OF VERTEX
struct Vertex_PosTex
{
	float x, y, z;
	float u, v;

	Vertex_PosTex( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		u = 0.0f;
		v = 0.0f;
	}
	Vertex_PosTex( float _x, float _y, float _z, float _u, float _v )
	{
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Wrapper for a DirectX9 vertex buffer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct IDirect3DVertexBuffer9;
struct IDirect3DVertexDeclaration9;
class kVertexBuffer
{
	IDirect3DVertexBuffer9*			m_Buffer;
	IDirect3DVertexDeclaration9*	m_Decl;
	Vertex_PosTex*					m_Verts;
	unsigned int					m_NumVerts;

public:
	kVertexBuffer( void );
	~kVertexBuffer( void );
	
	Vertex_PosTex* Lock( unsigned int _numVerts );
	bool Unlock( void );

	// Accessors
	inline IDirect3DVertexBuffer9* GetBuffer( void )	{ return m_Buffer;		}
	inline IDirect3DVertexDeclaration9* GetDecl( void )	{ return m_Decl;		}
	inline Vertex_PosTex* GetVerts( void )				{ return m_Verts;		}
	inline unsigned int GetNumVerts( void )				{ return m_NumVerts;	}
	// Mutators
	inline void SetBuffer( IDirect3DVertexBuffer9* _buffer )	{ m_Buffer = _buffer;		}
	inline void SetDecl( IDirect3DVertexDeclaration9* _decl )	{ m_Decl = _decl;			}
	inline void SetVerts( Vertex_PosTex* _verts )				{ m_Verts = _verts;			}
	inline void SetNumVerts( unsigned int _numVerts )			{ m_NumVerts = _numVerts;	}
};

#endif