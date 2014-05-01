#pragma once
#ifndef _COLLISION_COMPONENT_H_
#define _COLLISION_COMPONENT_H_

#include "kComponent.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Contains all information needed to check for, and handle, collision
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kCollisionResult;
class kCollisionVolume;
class kCollisionComponent : public kComponent
{
	kCollisionVolume* m_Volume;

	typedef void(*kCollisionCallback)(kGameObject*, kCollisionResult*);
	kCollisionCallback m_Callback;
public:
	kCollisionComponent( void );
	~kCollisionComponent( void );

	virtual void Release( void );	
	virtual void OnDock( kGameObject* _owner );
	virtual void OnUndock( void );
	virtual void Update( float _timing );

	void OnCollision( kCollisionResult* _result );

	void MakeRECT( float _offsetX, float _offsetY, float _halfWidth, float _halfHeight );
	void MakeCircle( float _offsetX, float _offsetY, float _radius );
	void MakeRay( float _offsetX, float _offsetY, float _dirX, float _dirY );
	void MakeCapsule( float _offsetX, float _offsetY, float _endX, float _endY, float _radius );


	// Accessors
	inline kCollisionVolume* GetVolume( void ) const { return m_Volume; }
	// Mutators
	inline void SetVolume( kCollisionVolume* _volume ) { m_Volume = _volume; }
};

#endif