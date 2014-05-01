#pragma once
#ifndef _COLLISION_VOLUMES_H_
#define _COLLISION_VOLUMES_H_

#include "directx9.h"

enum CollisionType
{
	Type_RECT = 0,
	Type_Circle,
	Type_Ray,
	Type_Capsule,

	Type_Num,
};

class kCollisionVolume
{
protected:
	CollisionType m_Type;
public:
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_OffsetPos;

	kCollisionVolume( CollisionType _type )
	{
		m_Type		= _type;
		m_Pos		= D3DXVECTOR2( 0.0f, 0.0f );
		m_OffsetPos = D3DXVECTOR2( 0.0f, 0.0f );
	}
	~kCollisionVolume( void ) {}

	// Accessors
	inline CollisionType GetType( void ) const		{ return m_Type;		}
	inline D3DXVECTOR2 GetPos( void ) const			{ return m_Pos;			}
	inline D3DXVECTOR2 GetOffsetPos( void ) const	{ return m_OffsetPos;	}
	// Mutators
	inline void SetPos( D3DXVECTOR2 _pos )				{ m_Pos = _pos;				}
	inline void SetOffsetPos( D3DXVECTOR2 _offsetPos )	{ m_OffsetPos = _offsetPos; }
};

class kRECT : public kCollisionVolume
{
public:
	float m_HalfWidth;
	float m_HalfHeight;

	kRECT( void ) : kCollisionVolume( Type_RECT )
	{
		m_HalfWidth		= 0.0f; 
		m_HalfHeight	= 0.0f;
	}
	kRECT( D3DXVECTOR2 _offsetPos, float _halfWidth, float _halfHeight ) : kCollisionVolume( Type_RECT )
	{
		m_OffsetPos		= _offsetPos;
		m_HalfWidth		= _halfWidth;
		m_HalfHeight	= _halfHeight; 
	}
	~kRECT( void ) {}
};

class kCircle : public kCollisionVolume
{
public:
	float m_Radius;

	kCircle( void ) : kCollisionVolume( Type_Circle )
	{
		m_Radius = 0.0f;
	}
	kCircle( D3DXVECTOR2 _offsetPos, float _radius ) : kCollisionVolume( Type_Circle )
	{
		m_OffsetPos = _offsetPos;
		m_Radius	= _radius;
	}
	~kCircle( void ) {}
};

class kRay : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_Dir;

	kRay( void ) : kCollisionVolume( Type_Ray )
	{
		m_Dir = D3DXVECTOR2( 0.0f, 0.0f );
	}
	kRay( D3DXVECTOR2 _offsetPos, D3DXVECTOR2 _dir ) : kCollisionVolume( Type_Ray )
	{
		m_OffsetPos = _offsetPos;
		m_Dir		= _dir; 
	}
	~kRay( void ) {}
};

class kCapsule : public kCollisionVolume
{
public:
	D3DXVECTOR2 m_End;
	float		m_Radius;

	kCapsule( void ) : kCollisionVolume( Type_Capsule )
	{
		m_End		= D3DXVECTOR2( 0.0f, 0.0f );
		m_Radius	= 0.0f; 
	}
	kCapsule( D3DXVECTOR2 _startOffset, D3DXVECTOR2 _end, float _radius  ) : kCollisionVolume( Type_Ray )
	{
		m_OffsetPos = _startOffset;
		m_End		= _end;
		m_Radius	= _radius; 
	}
	~kCapsule( void ) {}
};

#endif