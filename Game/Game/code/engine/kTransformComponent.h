#pragma once
#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include "kComponent.h"
#include "directx9.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Position data rolled up into one useful component
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kTransformComponent : public kComponent
{
	D3DXVECTOR2 m_Position;
	D3DXVECTOR2 m_Scale;
	float		m_Rotation;
public:
	kTransformComponent( void );
	kTransformComponent( D3DXVECTOR2 _position, 
						 D3DXVECTOR2 _scale, 
						 float _rotation );
	~kTransformComponent( void );

	virtual void Release( void ) {}
	
	virtual void OnDock( kGameObject* _owner );
	virtual void OnUndock( void );
	virtual void Update( float _timing );

	// Accessors
	inline D3DXVECTOR2 GetPosition( void ) const	{ return m_Position;	}
	inline D3DXVECTOR2 GetScale( void ) const		{ return m_Scale;		}
	inline float GetRotation( void ) const			{ return m_Rotation;	}

	// Mutators
	inline void SetPosition( D3DXVECTOR2 _position )	{ m_Position = _position;	}
	inline void SetScale( D3DXVECTOR2 _scale )			{ m_Scale = _scale;			}
	inline void SetRotation( float _rotation )			{ m_Rotation = _rotation;	}
};

#endif