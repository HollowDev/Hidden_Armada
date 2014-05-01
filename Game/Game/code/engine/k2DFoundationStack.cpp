#include "k2DFoundationStack.h"

k2DFoundationStack::kStack k2DFoundationStack::m_Stack[FOUNDATION_STACK_MAX];
int k2DFoundationStack::m_StackPos = 0;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Pushes a transform onto the stack
Params:
	_pos - the 2D position of the transform
	_scale - the 2D scale of the transform
	_rot - the rotation of the object on the Z axis
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void k2DFoundationStack::Push( D3DXVECTOR2* _pos, D3DXVECTOR2* _scale, float* _rot )
{
	D3DXVECTOR2 newPos		= m_Stack[m_StackPos].pos;
	D3DXVECTOR2 newScale	= m_Stack[m_StackPos].scale;
	float newRot			= m_Stack[m_StackPos].rot;

	newPos		+= *_pos;
	newScale	+= *_scale;
	newRot		+= *_rot;

	m_StackPos++;
	m_Stack[m_StackPos].pos		= newPos;
	m_Stack[m_StackPos].scale	= newScale;
	m_Stack[m_StackPos].rot		= newRot;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Grabs the data from the stack and saves it out for the user to process
Params:
	_pos - the 2D position of the transform to output
	_scale - the 2D scale of the transform to output
	_rot - the rotation of the object on the Z axis to output
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void k2DFoundationStack::Peek( D3DXVECTOR2* _pos, D3DXVECTOR2* _scale, float* _rot )
{
	_pos	= &m_Stack[m_StackPos].pos;
	_scale	= &m_Stack[m_StackPos].scale;
	_rot	= &m_Stack[m_StackPos].rot;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Grabs the data from the stack and saves it out for the user to process
Params:
	_mat - the matrix filled with the transforms from the stack to output
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void k2DFoundationStack::Peek( D3DXMATRIX* _mat )
{
	// TODO:: Convert the shit into a matrix
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Pops a transform from the k2DFoundationStack
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void k2DFoundationStack::Pop( void )
{
	m_StackPos--;
	if( m_StackPos < 0 )
	{
		// FUCKING PROBLEM!
		int x = 0;
	}
}
