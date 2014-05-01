#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "kObject.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: A self contained part of a object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kComponent : public kObject
{
	kObject* m_Owner;
public:
	virtual ~kComponent( void ) = 0 {}
	inline kObject* GetOwner( void )		{ return m_Owner;	}
	inline void SetOwner( kObject* _owner ) { m_Owner = _owner; }
};

#endif