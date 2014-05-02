#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "kObject.h"

#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: The base for all game tokens. 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kComponent;
class kTransformComponent;
class kGameObject : public kObject
{
protected:
	kGameObject*			m_Parent;
	vector< kGameObject* >	m_Children;
	vector< kComponent* >	m_Components;

	kTransformComponent*	m_Transform;

	void UpdateChildren( float _timing );
	void UpdateComponents( float _timing );
public:
	kGameObject( void );
	~kGameObject( void );

	virtual void Release( void );
	virtual void Update( float _timer );

	virtual void Dock( kGameObject* _child );
	virtual void Dock( kComponent* _component );
	virtual void Undock( kGameObject* _child );
	virtual void Undock( kComponent* _component );

	// Accessors
	inline kGameObject* GetParent( void )				{ return m_Parent;		}
	inline kTransformComponent* GetTransform( void )	{ return m_Transform;	}
	// Mutators
	inline void SetParent( kGameObject* _parent )				{ m_Parent = _parent;		}
	inline void SetTransform( kTransformComponent* _transform ) { m_Transform = _transform; }
};

#endif