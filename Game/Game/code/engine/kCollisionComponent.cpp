#include "kCollisionComponent.h"
#include "kCollisionVolumes.h"

#include "kCollisionSystem.h"
#include "k2DFoundationStack.h"
#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCollisionComponent::kCollisionComponent( void )
{
	m_Type = RTTI_kCollisionComponent;

	m_Volume = nullptr;
	m_Callback = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCollisionComponent::~kCollisionComponent( void )
{
	Release();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Releases all the data inside of this kCollisionComponent
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::Release( void )
{
	SAFE_DELETE( m_Volume );
	m_Callback = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called when the component is docked
Params:
	_owner - the owner to set for this component
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::OnDock( kGameObject* _owner )
{
	// Set the owner
	m_Owner = _owner;

	// Register the collider with the collision system
	g_CollisionSystem.RegisterCollider( this );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called when the component is undocked
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::OnUndock( void )
{
	// Unregister the collider with the collision system
	g_CollisionSystem.UnregisterCollider( this );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the collision component
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::Update( float _timing )
{
	// TODO:: Update the collision volume's position!
	if( m_Volume )
	{
		// TODO:: Must have the k2DFoundationStack completed first, to grab the parents info
		D3DXVECTOR2 pos, scale;
		float rot;
		k2DFoundationStack::Peek( &pos, &scale, &rot );
		m_Volume->SetPos( pos + m_Volume->GetOffsetPos() );
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Is called when the component has collided with another component.
Params:
	_result - the information from the collision
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::OnCollision( kCollisionResult* _result ) 
{ 
	if( m_Callback ) m_Callback( m_Owner, _result ); 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called to construct the volume as a RECT
Params:
	_offsetX - the offset to use for the position when inheriting on the X axis
	_offsetY - the offset to use for the position when inheriting on the Y axis
	_halfWidth - half the width of the RECT
	_halfHeight - half the height of the RECT
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::MakeRECT( float _offsetX, float _offsetY, float _halfWidth, float _halfHeight )
{
	m_Volume = new kRECT( D3DXVECTOR2(_offsetX, _offsetY), _halfWidth, _halfHeight ); 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called to construct the volume as a Circle
Params:
	_offsetX - the offset to use for the position when inheriting on the X axis
	_offsetY - the offset to use for the position when inheriting on the Y axis
	_radius - the radius to use for this circle
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::MakeCircle( float _offsetX, float _offsetY, float _radius )
{
	m_Volume = new kCircle( D3DXVECTOR2(_offsetX, _offsetY), _radius ); 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called to construct the volume as a Ray
Params:
	_offsetX - the offset to use for the position when inheriting on the X axis
	_offsetY - the offset to use for the position when inheriting on the Y axis
	_dirX - the direction the ray is heading on the X axis
	_dirY - the direction the ray is heading on the Y axis
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::MakeRay( float _offsetX, float _offsetY, float _dirX, float _dirY )
{
	m_Volume = new kRay( D3DXVECTOR2(_offsetX, _offsetY), D3DXVECTOR2(_dirX, _dirY) ); 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Called to construct the volume as a Capsule
Params:
	_offsetX - the offset to use for the position when inheriting on the X axis
	_offsetY - the offset to use for the position when inheriting on the Y axis
	_endX - the end position of the capsule
	_endY - the end position of the capsule
	_radius - the radius to use for the start and end circles
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionComponent::MakeCapsule( float _offsetX, float _offsetY, float _endX, float _endY, float _radius )
{
	m_Volume = new kCapsule( D3DXVECTOR2(_offsetX, _offsetY), D3DXVECTOR2(_endX, _endY), _radius ); 
}
