#pragma once
#ifndef _COLLISION_LIBRARY_H_
#define _COLLISION_LIBRARY_H_

// TODO:: Make this less ugly.

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Call CheckCollision and it determines the rest. MATHGIC
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kCollisionVolume;
class kCollisionResult;
class kRECT;
class kCircle;
class kRay;
class kCapsule;
class kCollisionLibrary
{
public:
	static bool CheckCollision( kCollisionVolume* _volume1, 
								kCollisionVolume* _volume2,
								kCollisionResult* _result1,
								kCollisionResult* _result2 );

private:
	// RECT
	static bool RECTvsRECT( kRECT* _rect1, kRECT* _rect2, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RECTvsCircle( kRECT* _rect, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RECTvsRay( kRECT* _rect, kRay* _ray,  kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RECTvsCapsule( kRECT* _rect, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 );

	// CIRCLE
	static bool CircleVsRECT( kCircle* _circle, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CircleVsCircle( kCircle* _circle1, kCircle* _circle2, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CircleVsRay( kCircle* _circle, kRay* _ray, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CircleVsCapsule( kCircle* _circle, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 );

	// RAY
	static bool RayVsRECT( kRay* _ray, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RayVsCircle( kRay* _ray, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RayVsRay( kRay* _ray1, kRay* _ray2, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool RayVsCapsule( kRay* _ray, kCapsule* _capsule, kCollisionResult* _result1, kCollisionResult* _result2 );

	// Capsule
	static bool CapsuleVsRECT( kCapsule* _capsule, kRECT* _rect, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CapsuleVsCircle( kCapsule* _capsule, kCircle* _circle, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CapsuleVsRay( kCapsule* _capsule, kRay* _ray, kCollisionResult* _result1, kCollisionResult* _result2 );
	static bool CapsuleVsCapsule( kCapsule* _capsule1, kCapsule* _capsule2, kCollisionResult* _result1, kCollisionResult* _result2 );

};

#endif