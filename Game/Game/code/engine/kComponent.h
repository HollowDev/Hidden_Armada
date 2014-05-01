#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "kObject.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: A self contained part of a object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kGameObject;
class kComponent : public kObject
{
protected:
	kGameObject* m_Owner;
public:
	virtual ~kComponent( void ) = 0 {}

	virtual void OnDock( kGameObject* _owner ) = 0;
	virtual void OnUndock( void ) = 0;

	inline kGameObject* GetOwner( void )		{ return m_Owner;	}
	inline void SetOwner( kGameObject* _owner ) { m_Owner = _owner; }
};

#endif