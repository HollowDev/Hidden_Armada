#pragma once
#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: The interface for the states for use in the kStateSystem
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kWinApp;
class kBaseState
{
protected:
	kWinApp* m_App;

public:
	virtual ~kBaseState( void ) = 0 {}

	virtual void Initialize( kWinApp* _app ) = 0;
	virtual void Release( void ) = 0;
	virtual void Update( float _timing ) = 0;
};

#endif