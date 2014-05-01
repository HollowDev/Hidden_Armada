#include "kRenderObjectDebug.h"
#include "kVertexBuffer.h"
#include "kIndexBuffer.h"

#include "kD3D9Handler.h"
#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderObjectDebug::kRenderObjectDebug( void )
{
	m_VertexBuffer	= nullptr;
	m_IndexBuffer	= nullptr;
	m_RenderColor	= D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	D3DXMatrixIdentity( &m_WorldMat );

	m_PrimitiveType = D3DPT_LINELIST;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderObjectDebug::~kRenderObjectDebug( void )
{
	SAFE_DELETE( m_VertexBuffer );
	SAFE_DELETE( m_IndexBuffer );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Renders the debug object!
Params:
	_renderPass - the render pass used on this object
	_effect - the effect used on this object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderObjectDebug::Render( kRenderPass* _renderPass, ID3DXEffect* _effect )
{
	_effect->SetMatrix( "gWorld", &m_WorldMat );
	_effect->SetVector( "gRenderColor", &m_RenderColor );
	_effect->CommitChanges();

	IDirect3DVertexBuffer9* vbuffer		= m_VertexBuffer->GetBuffer();
	IDirect3DVertexDeclaration9* decl	= m_VertexBuffer->GetDecl();
	IDirect3DIndexBuffer9* ibuffer		= m_IndexBuffer->GetBuffer();

	unsigned int numVerts	= m_VertexBuffer->GetNumVerts();
	unsigned int numIndices = m_IndexBuffer->GetNumIndices();
	unsigned int numPrimitives = numIndices / 2;

	if( m_PrimitiveType == D3DPT_TRIANGLELIST )
		numPrimitives = numIndices / 3;

	kD3D9Handler::m_Device->SetVertexDeclaration( decl );
	kD3D9Handler::m_Device->SetStreamSource( 0, vbuffer, 0, sizeof(Vertex_PosTex) );
	kD3D9Handler::m_Device->SetIndices( ibuffer );
	kD3D9Handler::m_Device->DrawIndexedPrimitive( m_PrimitiveType, 0, 0, numVerts, 0, numPrimitives );
}
