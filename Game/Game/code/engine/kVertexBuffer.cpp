#include "kVertexBuffer.h"
#include "kVertexFormat.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Create the vertex declaration based on the templated type
Return:
	bool - True if successfully built else false.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename VERTEX>
void kVertexBuffer<VERTEX>::CreateVertexDecl( void )
{
	// IF IT GETS IN HERE THAT MEANS YOU HAVEN'T DELCARED THAT VERTEX TYPES DECL
	int x = 0;
}

template<>
void kVertexBuffer<kVertex_Pos>::CreateVertexDecl( void )
{
	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END(),
	};
	kD3D9Handler::m_Device->CreateVertexDeclaration( decl, &m_Decl );
}

template<>
void kVertexBuffer<kVertex_PosTex>::CreateVertexDecl( void )
{
	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END(),
	};
	kD3D9Handler::m_Device->CreateVertexDeclaration( decl, &m_Decl );
}

template<>
void kVertexBuffer<kVertex_PosNormTex>::CreateVertexDecl( void )
{
	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
		D3DDECL_END(),
	};
	kD3D9Handler::m_Device->CreateVertexDeclaration( decl, &m_Decl );
}