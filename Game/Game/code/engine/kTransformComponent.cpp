#include "kTransformComponent.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kTransformComponent::kTransformComponent( void )
{
	m_Type = RTTI_kTransformComponent;
	m_Position	= D3DXVECTOR2( 0.0f, 0.0f );
	m_Scale		= D3DXVECTOR2( 1.0f, 1.0f );
	m_Rotation	= 0.0f;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Overloaded constructor
Params:
	_position - the position for this transform
	_scale - the scale for this transform
	_rotation - the rotatino for this transform
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kTransformComponent::kTransformComponent( 
	D3DXVECTOR2 _position, 
	D3DXVECTOR2 _scale, 
	float _rotation 
	)
{
	m_Type = RTTI_kTransformComponent;
	m_Position	= _position;
	m_Scale		= _scale;
	m_Rotation	= _rotation;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kTransformComponent::~kTransformComponent( void )
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called when the component is docked
Params:
	_owner - the owner to set for this component
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kTransformComponent::OnDock( kGameObject* _owner )
{
	m_Owner = _owner;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called when the component is undocked from it's owner
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kTransformComponent::OnUndock( void )
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the transform component
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kTransformComponent::Update( float _timing )
{
}
