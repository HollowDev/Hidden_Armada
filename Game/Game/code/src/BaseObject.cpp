#include "BaseObject.h"
#include "../engine/kComponent.h"
#include "../engine/kCollisionComponent.h"

BaseObject::BaseObject( void )
{
}

BaseObject::~BaseObject( void )
{
}

void BaseObject::Release( void )
{
}

void BaseObject::Update( float _timer )
{
	kGameObject::Update( _timer );
}

void BaseObject::Dock( kComponent* _component )
{
	kGameObject::Dock( _component );
	// If it's a collision component save dat shit!.. I actually don't know why...
	if( _component->GetType() == RTTI_kCollisionComponent )
	{
		// Set the callback to the BaseObject callback func
		m_Collider = (kCollisionComponent*)_component;
		m_Collider->SetCallback( BaseObject::CollisionCallback );
	}
}

void BaseObject::Undock( kComponent* _component )
{
	kGameObject::Undock( _component );
}

void BaseObject::HandleCollision( kCollisionResult* _result )
{
	int x = 0;
}

void BaseObject::CollisionCallback( kGameObject* _object, kCollisionResult* _result )
{
	BaseObject* baseObject = dynamic_cast< BaseObject* >( _object );
	if( baseObject ) 
		baseObject->HandleCollision( _result );
}
