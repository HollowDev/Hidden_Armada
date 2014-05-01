#include "kRenderSystem.h"
#include "kRenderPass.h"

#include "kD3D9Handler.h"
#include "kRenderParams.h"

kRenderSystem g_RenderSystem;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderSystem::kRenderSystem( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderSystem::~kRenderSystem( void )
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Initializes the kRenderSystem, adding all of the global kRenderPasses to it's list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderSystem::Initialize( void )
{
	// ADD ALL THE RENDER PASSES HERE, FROM RENDER PARAMS
	m_RenderPasses.push_back( &g_RenderPassDebug );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Renders all of the objects inside of all of the kRenderPasses
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderSystem::Render( void )
{
	kD3D9Handler::m_Device->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 255, 25, 25, 50 ), 1.0f, 0 );
	{
		vector< kRenderPass* >::iterator iter = m_RenderPasses.begin();
		for( iter; iter != m_RenderPasses.end(); ++iter )
		{
			(*iter)->Render();
		}
	}
	kD3D9Handler::m_Device->Present(0,0,0,0);
}
