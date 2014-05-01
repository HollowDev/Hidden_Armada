#pragma once
#ifndef _COLLISION_RESULT_H_
#define _COLLISION_RESULT_H_

#include "directx9.h"

class kCollisionResult
{
public:
	int			m_OtherType;
	float		m_Length;
	D3DXVECTOR2 m_Normal;
};

#endif