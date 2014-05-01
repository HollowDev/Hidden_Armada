#pragma once
#ifndef _COLLISION_LIBRARY_H_
#define _COLLISION_LIBRARY_H_

#include "kCollisionVolumes.h"

struct kCollisionResult
{
	float		m_Length;
	D3DXVECTOR2 m_Normal;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Call CheckCollision and it determines the rest. MATHGIC
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kCollisionLibrary
{
public:
	static bool CheckCollision( kCollisionVolume* _volume1, 
								kCollisionVolume* _volume2,
								kCollisionResult& _result1,
								kCollisionResult& _result2 );

private:
	// RECT
	static bool RECTvsRECT( kRECT* _rect1, kRECT* _rect2, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RECTvsCircle( kRECT* _rect, kCircle* _circle, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RECTvsRay( kRECT* _rect, kRay* _ray,  kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RECTvsLine( kRECT* _rect, kLine* _line,  kCollisionResult& _result1, kCollisionResult& _result2 );

	// CIRCLE
	static bool CircleVsRECT( kCircle* _circle, kRECT* _rect, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool CircleVsCircle( kCircle* _circle1, kCircle* _circle2, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool CircleVsRay( kCircle* _circle, kRay* _ray, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool CircleVsLine( kCircle* _circle, kLine* _line, kCollisionResult& _result1, kCollisionResult& _result2 );

	// RAY
	static bool RayVsRECT( kRay* _ray, kRECT* _rect, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RayVsCircle( kRay* _ray, kCircle* _circle, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RayVsRay( kRay* _ray1, kRay* _ray2, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool RayVsLine( kRay* _ray, kLine* _line, kCollisionResult& _result1, kCollisionResult& _result2 );

	// LINE
	static bool LineVsRECT( kLine* _line, kRECT* _rect, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool LineVsCircle( kLine* _line, kCircle* _circle, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool LineVsRay( kLine* _line, kRay* _ray, kCollisionResult& _result1, kCollisionResult& _result2 );
	static bool LineVsLine( kLine* _line1, kLine* _line2, kCollisionResult& _result1, kCollisionResult& _result2 );
};

#endif