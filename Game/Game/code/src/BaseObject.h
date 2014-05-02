#pragma once
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "../engine/kGameObject.h"
#include "../engine/kCollisionResult.h"

class kCollisionComponent;
class BaseObject : public kGameObject
{
	kCollisionComponent* m_Collider;

public:
	BaseObject( void );
	~BaseObject( void );

	virtual void Release( void );
	virtual void Update( float _timer );

	virtual void Dock( kComponent* _component );
	virtual void Undock( kComponent* _component );
	
	virtual void HandleCollision( kCollisionResult* _result );
	static void CollisionCallback( kGameObject* _object, kCollisionResult* _result );
};

#endif