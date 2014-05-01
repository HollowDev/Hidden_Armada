#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "windows.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Tracks the total time, time since last frame and FPS of the game.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kTimer
{
	float			m_TimeStart;
	float			m_DeltaTime;
	float			m_TimePrevious;
	float			m_TimeLastFrame;
	int				m_FPS;
	int				m_Frames;
	int				m_TotalFrames;
	LARGE_INTEGER	m_TickFrequency;

public:
	kTimer( void );
	~kTimer( void );

	void Initialize( void );
	void Reset( void );
	void Update( void );

	// Accessors
	float GetTime( void );
	float GetDeltaTime( void ) const	{ return m_DeltaTime; }
	int GetFPS( void ) const			{ return m_FPS; }
	int GetTotalFrames( void ) const	{ return m_TotalFrames; }
};

#endif