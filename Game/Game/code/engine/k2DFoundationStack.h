#pragma once
#ifndef _2D_FOUNDATION_STACK_H_
#define _2D_FOUNDATION_STACK_H_

#include "directx9.h"

#define FOUNDATION_STACK_MAX	32

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: A stack of transforms that can inherit off of each other. 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class k2DFoundationStack
{
	struct kStack
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 scale;
		float rot;

		kStack( void ) : pos(0.0f,0.0f), scale(1.0f,1.0f), rot(0.0f) {}
	};

	static kStack m_Stack[FOUNDATION_STACK_MAX];
	static int m_StackPos;

public:
	static void Push( D3DXVECTOR2* _pos, D3DXVECTOR2* _scale, float* _rot );
	static void Peek( D3DXVECTOR2* _pos, D3DXVECTOR2* _scale, float* _rot );
	static void Peek( D3DXMATRIX* _mat );
	static void Pop( void );
};

#endif