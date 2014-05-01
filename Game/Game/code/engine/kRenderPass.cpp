#include "kRenderPass.h"
#include "kCamera.h"
#include "kRenderObject.h"

#include "kD3D9Handler.h"
#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderPass::kRenderPass( void )
{
	m_Effect = nullptr;
	m_Camera = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kRenderPass::~kRenderPass( void )
{
	SAFE_RELEASE( m_Effect );
	m_Camera = nullptr;
	m_RenderObjects.clear();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the current states
Params:
	_effectFilePath - the effect/shader file to load and use for this kRenderPass
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderPass::Initialize( LPCWSTR _effectFilePath )
{
	// Load the effect
	D3DXCreateEffectFromFile( kD3D9Handler::m_Device, _effectFilePath, 0, 0, 0, 0, &m_Effect, 0 );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Renders all of the RenderObjects current in this kRenderPass
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderPass::Render( void )
{
	// TODO:: SORT THE RENDER LIST IF IT'S DIRTY (been changed)

	kD3D9Handler::m_Device->Clear( 0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 255, 0, 0, 0 ), 1.0f, 0 );
	kD3D9Handler::m_Device->BeginScene();
	{
		kD3D9Handler::m_Device->SetRenderState( D3DRENDERSTATETYPE::D3DRS_ALPHABLENDENABLE, TRUE );
		kD3D9Handler::m_Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		kD3D9Handler::m_Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		// Render the objects
		unsigned passes(0);
		m_Effect->Begin(&passes, 0);
		for(unsigned int i = 0; i < passes; ++i)
		{
			m_Effect->BeginPass(i);
			{
				// Set up the camera variables in the shader
				if( m_Camera )
				{
					m_Effect->SetMatrix( "gView",			&m_Camera->GetView()		);
					m_Effect->SetMatrix( "gProjection",		&m_Camera->GetProj()		);
					m_Effect->SetMatrix( "gViewProjection", &m_Camera->GetViewProj()	);
				}

				// Go through the list and render each object
				vector< kRenderObject* >::iterator iter = m_RenderObjects.begin();
				for( iter; iter != m_RenderObjects.end(); ++iter )
				{
					(*iter)->Render( this, m_Effect );
				}
			}
			m_Effect->EndPass();
		}
		m_Effect->End();

	}
	kD3D9Handler::m_Device->EndScene();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Adds a kRenderObject to the render list
Params:
	_renderObject - the kRenderObject to add to the render list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderPass::AddRenderObject( kRenderObject* _renderObject )
{
	m_RenderObjects.push_back( _renderObject );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Removes a kRenderObject from the render list
Params:
	_renderObject - the kRenderObject to remove from the render list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kRenderPass::RemoveRenderObject( kRenderObject* _renderObject )
{
	vector< kRenderObject* > newList;
	for( unsigned int i = 0; i < m_RenderObjects.size(); ++i )
	{
		if( m_RenderObjects[i] != _renderObject )
			newList.push_back( m_RenderObjects[i] );
	}

	m_RenderObjects.clear();
	m_RenderObjects = newList;
}