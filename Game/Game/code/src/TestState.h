#pragma once
#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "../engine/kBaseState.h"

class kCamera;
class kDebugDraw;
class TestState : public kBaseState
{
	kCamera* m_DebugCam;
	kDebugDraw* m_DebugDraw;

public:
	TestState( void );
	~TestState( void );

	void Initialize( kWinApp* _app );
	void Release( void );
	void Update( float _timing );
};

#endif