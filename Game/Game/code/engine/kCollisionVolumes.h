#pragma once
#ifndef _COLLISION_VOLUMES_H_
#define _COLLISION_VOLUMES_H_

#include "directx9.h"

enum CollisionType
{
	Type_RECT = 0,
	Type_Circle,
	Type_Ray,
	Type_Line,

	Type_Num,
};

class kCollisionVolume
{
protected:
	CollisionType m_Type;
public:
	kCollisionVolume( CollisionType _type ) : m_Type( _type ) {}
	inline CollisionType GetType( void ) { return m_Type; }
};

class kRECT : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_Pos;
	float m_HalfWidth;
	float m_HalfHeight;

	kRECT( void ) : 
		kCollisionVolume( Type_RECT ),
		m_Pos( 0.0f, 0.0f ), 
		m_HalfWidth( 0.0f ), 
		m_HalfHeight( 0.0f ) {}
	kRECT( D3DXVECTOR2 _pos, float _halfWidth, float _halfHeight ) : 
		kCollisionVolume( Type_RECT ),
		m_Pos( _pos ), 
		m_HalfWidth( _halfWidth ), 
		m_HalfHeight( _halfHeight ) {}
	~kRECT( void ) {}
};

class kCircle : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_Pos;
	float m_Radius;

	kCircle( void ) : 
		kCollisionVolume( Type_Circle ),
		m_Pos( 0.0f, 0.0f ),
		m_Radius( 0.0f ) {}
	kCircle( D3DXVECTOR2 _pos, float _radius ) :
		kCollisionVolume( Type_Circle ),
		m_Pos( _pos ),
		m_Radius( _radius ) {}
	~kCircle( void ) {}
};

class kRay : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Dir;

	kRay( void ) : 
		kCollisionVolume( Type_Ray ),
		m_Pos( 0.0f, 0.0f ),
		m_Dir( 0.0f, 0.0f ) {}
	kRay( D3DXVECTOR2 _pos, D3DXVECTOR2 _dir ) :
		kCollisionVolume( Type_Ray ),
		m_Pos( _pos ),
		m_Dir( _dir ) {}
	~kRay( void ) {}
};

class kLine : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_Start;
	D3DXVECTOR2 m_End;

	kLine( void ) : 
		kCollisionVolume( Type_Line ),
		m_Start( 0.0f, 0.0f ),
		m_End( 0.0f, 0.0f ) {}
	kLine( D3DXVECTOR2 _start, D3DXVECTOR2 _end ) :
		kCollisionVolume( Type_Line ),
		m_Start( _start ),
		m_End( _end ) {}
	~kLine( void ) {}
};

#endif