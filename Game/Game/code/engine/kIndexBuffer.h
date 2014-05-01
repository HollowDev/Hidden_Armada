#pragma once
#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Wrapper for a DirectX9 index buffer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct IDirect3DIndexBuffer9;
class kIndexBuffer
{
	IDirect3DIndexBuffer9*	m_Buffer;
	unsigned int*			m_Indices;
	unsigned int			m_NumIndices;
public:
	kIndexBuffer( void );
	~kIndexBuffer( void );

	unsigned int* Lock( unsigned int _numIndices );
	bool Unlock( void );

	// Accessors
	inline IDirect3DIndexBuffer9* GetBuffer( void )	{ return m_Buffer;		}
	inline unsigned int* GetIndices( void )			{ return m_Indices;		}
	inline unsigned int GetNumIndices( void )		{ return m_NumIndices;	}
	// Mutators
	inline void SetBuffer( IDirect3DIndexBuffer9* _buffer )	{ m_Buffer = _buffer;			}
	inline void SetIndices( unsigned int* _indices )		{ m_Indices = _indices;			}
	inline void SetNumIndices( unsigned int _numIndices )	{ m_NumIndices = _numIndices;	}
};

#endif