#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

enum ObjectType
{
	RTTI_kTransformComponent = 0,
	RTTI_kAniminstance,
	RTTI_kGameObject,

	RTTI_Num
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: The atom of the game. Everything... Everything is created off of this.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kObject
{
protected:
	ObjectType m_Type;
public:
	virtual ~kObject( void ) = 0 {}
	virtual void Release( void ) = 0;
	virtual void Update( float _timing ) = 0;
	inline ObjectType GetType( void ) { return m_Type; }
};

#endif