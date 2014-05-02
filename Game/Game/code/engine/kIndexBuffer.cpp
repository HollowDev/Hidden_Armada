#include "kIndexBuffer.h"
#include "directx9.h"

#include "memory_macros.h"
#include "kD3D9Handler.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kIndexBuffer::kIndexBuffer( void )
{
	m_Buffer		= nullptr;
	m_Indices		= nullptr;
	m_NumIndices	= 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kIndexBuffer::~kIndexBuffer( void )
{
	SAFE_RELEASE( m_Buffer );
	SAFE_DELETE( m_Indices );
	m_NumIndices = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: 'Locks' the index buffer so you can construct the new indicies
Params:
	_numIndicies - the number of indices you will be needing
Return:
	unsigned int* - Pointer to the indicies
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned int* kIndexBuffer::Lock( unsigned int _numIndices )
{
	if( m_Indices ) SAFE_DELETE( m_Indices );

	m_NumIndices = _numIndices;
	m_Indices = new unsigned int[m_NumIndices];
	return m_Indices;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Create the index buffer.
Return:
	bool - True if successfully built else false.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kIndexBuffer::Unlock( void )
{
	if( !m_Indices || m_NumIndices == 0 ) return false;

	// Create the index buffer
	HRESULT hr = kD3D9Handler::m_Device->CreateIndexBuffer( sizeof(unsigned int) * m_NumIndices, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_Buffer, 0 );
	if( FAILED( hr ) ) return false;
	
	void *vram = 0;
	hr = m_Buffer->Lock( 0, 0, &vram, 0 );
	if( FAILED( hr ) ) return false;
	{
		memcpy( vram, m_Indices, sizeof(unsigned int) * m_NumIndices );
	}
	m_Buffer->Unlock();
	if( FAILED( hr ) ) return false;

	return true;
}
