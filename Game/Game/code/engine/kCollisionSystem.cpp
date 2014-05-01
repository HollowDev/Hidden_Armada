#include "kCollisionSystem.h"
#include "kCollisionComponent.h"

#include "kCollisionResult.h"
#include "kCollisionVolumes.h"
#include "kCollisionLibrary.h"
#include "kGameObject.h"

kCollisionSystem g_CollisionSystem;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCollisionSystem::kCollisionSystem( void )
{
	m_CheckCollision = true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kCollisionSystem::~kCollisionSystem( void )
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Clears out all of the colliders
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionSystem::Clear( void )
{
	m_Colliders.clear();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the collision system, checking for collision
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionSystem::Update( float _timing )
{
	// TODO:: Quad tree here?
	if( !m_CheckCollision ) return;

	// Right nw just loop through them all
	for( unsigned int i = 0; i < m_Colliders.size(); ++i )
	{
		kCollisionComponent* collider1 = m_Colliders[i];
		for( unsigned int j = 0; j < m_Colliders.size(); ++j )
		{
			kCollisionComponent* collider2 = m_Colliders[j];

			kCollisionResult result1, result2;
			if( kCollisionLibrary::CheckCollision( collider1->GetVolume(), collider2->GetVolume(), &result1, &result2 ) )
			{
				result1.m_OtherType = collider2->GetOwner()->GetType();
				result2.m_OtherType = collider1->GetOwner()->GetType();

				collider1->OnCollision(&result1);
				collider2->OnCollision(&result2);
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Set up a collider to register with the collision system
Params:
	_collider - the collider to register
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionSystem::RegisterCollider( kCollisionComponent* _collider )
{
	m_Colliders.push_back( _collider );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Set up a collider to unregister with the collision system
Params:
	_collider - the collider to unregister
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kCollisionSystem::UnregisterCollider( kCollisionComponent* _collider )
{
	for( unsigned int i = 0; i < m_Colliders.size(); ++i )
	{
		if( _collider == m_Colliders[i] )
		{
			m_Colliders.erase( m_Colliders.begin() + i );
			break;
		}
	}
}
