#include "kCollisionLibrary.h"
#include "kCollisionVolumes.h"
#include "kCollisionResult.h"

// TODO:: Make this less ugly.


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Checks collision between the two volumes, and stores the results.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kCollisionLibrary::CheckCollision( 
	kCollisionVolume* _volume1, 
	kCollisionVolume* _volume2,
	kCollisionResult* _result1,
	kCollisionResult* _result2 
	)
{
	if( _volume1->GetType() == Type_RECT )
	{
		if( _volume2->GetType() == Type_RECT )
			return RECTvsRECT( (kRECT*)_volume1, (kRECT*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Circle )
			return RECTvsCircle( (kRECT*)_volume1, (kCircle*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Ray )
			return RECTvsRay( (kRECT*)_volume1, (kRay*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Capsule )
			return RECTvsCapsule( (kRECT*)_volume1, (kCapsule*)_volume2, _result1, _result2 );
	}
	else if( _volume1->GetType() == Type_Circle )
	{
		if( _volume2->GetType() == Type_RECT )
			return CircleVsRECT( (kCircle*)_volume1, (kRECT*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Circle )
			return CircleVsCircle( (kCircle*)_volume1, (kCircle*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Ray )
			return CircleVsRay( (kCircle*)_volume1, (kRay*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Capsule )
			return CircleVsCapsule( (kCircle*)_volume1, (kCapsule*)_volume2, _result1, _result2 );
	}
	else if( _volume1->GetType() == Type_Ray )
	{
		if( _volume2->GetType() == Type_RECT )
			return RayVsRECT( (kRay*)_volume1, (kRECT*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Circle )
			return RayVsCircle( (kRay*)_volume1, (kCircle*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Ray )
			return RayVsRay( (kRay*)_volume1, (kRay*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Capsule )
			return RayVsCapsule( (kRay*)_volume1, (kCapsule*)_volume2, _result1, _result2 );
	}
	else if( _volume1->GetType() == Type_Capsule )
	{
		if( _volume2->GetType() == Type_RECT )
			return CapsuleVsRECT( (kCapsule*)_volume1, (kRECT*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Circle )
			return CapsuleVsCircle( (kCapsule*)_volume1, (kCircle*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Ray )
			return CapsuleVsRay( (kCapsule*)_volume1, (kRay*)_volume2, _result1, _result2 );
		else if( _volume2->GetType() == Type_Capsule )
			return CapsuleVsCapsule( (kCapsule*)_volume1, (kCapsule*)_volume2, _result1, _result2 );
	}

	return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: RECT COLLISION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kCollisionLibrary::RECTvsRECT( kRECT* _rect1, kRECT* _rect2, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	// Early outs
	if( _rect1->m_Pos.x - _rect1->m_HalfWidth >= _rect2->m_Pos.x + _rect2->m_HalfWidth ) return false;		// left		vs right
	if( _rect1->m_Pos.x + _rect1->m_HalfWidth <= _rect2->m_Pos.x - _rect2->m_HalfWidth ) return false;		// right	vs left
	if( _rect1->m_Pos.y - _rect1->m_HalfHeight >= _rect2->m_Pos.y + _rect2->m_HalfHeight ) return false;	// bottom	vs top
	if( _rect1->m_Pos.y + _rect1->m_HalfHeight <= _rect2->m_Pos.y - _rect2->m_HalfHeight ) return false;	// top		vs bottom

	// Calculate the collision information

	return true;
}
bool kCollisionLibrary::RECTvsCircle( kRECT* _rect, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}
bool kCollisionLibrary::RECTvsRay( kRECT* _rect, kRay* _ray, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}
bool kCollisionLibrary::RECTvsCapsule( kRECT* _rect, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: CIRCLE COLLISION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kCollisionLibrary::CircleVsRECT( kCircle* _circle, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return RECTvsCircle( _rect, _circle, _result2, _result1 );
}	
bool kCollisionLibrary::CircleVsCircle( kCircle* _circle1, kCircle* _circle2, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// Calculate the direction from the two positions
	D3DXVECTOR2 dir = _circle1->m_Pos - _circle2->m_Pos;
	// Calculate the distance between the two circles
	float dist = D3DXVec2Length( &dir );

	// If the distance is less than the combined radius then they don't collide. EARLY OUT
	if( dist < _circle1->m_Radius + _circle2->m_Radius ) return false;

	// If it gets here there is a collision, so calculate collision results
	
	// Determine the amount to seperate by
	dist = dist - (_circle1->m_Radius + _circle2->m_Radius);
	// Normalize the direction to get the normal of the collision
	D3DXVec2Normalize( &dir, &dir );

	// Save the information of the collision in the appropriate collision results
	_result1->m_Length = dist;
	_result1->m_Normal = dir;
	_result2->m_Length = -dist; // the other object heads in the other direction
	_result2->m_Normal = dir;
	
	return true;
}
bool kCollisionLibrary::CircleVsRay( kCircle* _circle, kRay* _ray, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}
bool kCollisionLibrary::CircleVsCapsule( kCircle* _circle, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: RAY COLLISION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kCollisionLibrary::RayVsRECT( kRay* _ray, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return RECTvsRay( _rect, _ray, _result2, _result1 );
}
bool kCollisionLibrary::RayVsCircle( kRay* _ray, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return CircleVsRay( _circle, _ray, _result2, _result1 );
}
bool kCollisionLibrary::RayVsRay( kRay* _ray1, kRay* _ray2, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}
bool kCollisionLibrary::RayVsCapsule( kRay* _ray, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: CAPSULE COLLISION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool kCollisionLibrary::CapsuleVsRECT( kCapsule* _capsule, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return RECTvsCapsule( _rect, _capsule, _result2, _result1 );
}
bool kCollisionLibrary::CapsuleVsCircle( kCapsule* _capsule, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return CircleVsCapsule( _circle, _capsule, _result2, _result1 );
}
bool kCollisionLibrary::CapsuleVsRay( kCapsule* _capsule, kRay* _ray, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	return RayVsCapsule( _ray, _capsule, _result2, _result1 );
}
bool kCollisionLibrary::CapsuleVsCapsule( kCapsule* _capsule1, kCapsule* _capsule2, kCollisionResult* _result1, kCollisionResult* _result2 )
{
	// TODO::
	return false;
}
