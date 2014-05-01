#pragma once
#ifndef _COLLISION_SYSTEM_H_
#define _COLLISION_SYSTEM_H_

#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Handles all collision in the game. Every kCollisionComponent is registered with this
	  system, if it is active, and is then processed every frame for collision. If a
	  collision occurs it calls the objects func* to let it know.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kCollisionComponent;
class kCollisionSystem
{
	bool m_CheckCollision;
	vector< kCollisionComponent* > m_Colliders;

public:
	kCollisionSystem( void );
	~kCollisionSystem( void );

	void Clear( void );
	void Update( float _timing );

	void RegisterCollider( kCollisionComponent* _collider );
	void UnregisterCollider( kCollisionComponent* _collider );

	// Accessors
	inline bool GetCheckCollision( void ) { return m_CheckCollision; }
	// Mutators
	inline void SetCheckCollision( bool _checkCollision ) { m_CheckCollision = _checkCollision; }
};

extern kCollisionSystem g_CollisionSystem;

#endif