#pragma once
#ifndef _VERTEX_FORMAT_H_
#define _VERTEX_FORMAT_H_

struct kVertex_Pos
{
	float x, y, z;

	kVertex_Pos( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	kVertex_Pos( float _x, float _y, float _z )
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct kVertex_PosTex
{
	float x, y, z;
	float u, v;

	kVertex_PosTex( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		u = 0.0f;
		v = 0.0f;
	}
	kVertex_PosTex( float _x, float _y, float _z, float _u, float _v )
	{
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}
};

struct kVertex_PosNormTex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	kVertex_PosNormTex( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		nx = 0.0f;
		ny = 0.0f;
		nz = 0.0f;
		u = 0.0f;
		v = 0.0f;
	}
	kVertex_PosNormTex( float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v )
	{
		x = _x;
		y = _y;
		z = _z;
		nx = _nx;
		ny = _ny;
		nz = _nz;
		u = _u;
		v = _v;
	}
};

#endif