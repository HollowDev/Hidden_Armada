#pragma once
#ifndef _STATE_SYSTEM_H_
#define _STATE_SYSTEM_H_

#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Handles the states in teh game. Safely changes, adds and removes them.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kWinApp;
class kBaseState;
class kStateSystem
{
	kWinApp* m_App;
	vector<kBaseState*> m_States;
	
	kBaseState*			m_ToChange;
	vector<kBaseState*> m_ToAdd;
	vector<kBaseState*> m_ToRemove;

	void ProcessChanges( void );
	void ProcessToChange( void );
	void ProcessToAdd( void );
	void ProcessToRemove( void );
public:
	kStateSystem( void );
	~kStateSystem( void );

	void Initialize( kWinApp* _winApp, kBaseState* _state );
	void Release( void );
	void Update( float _timing );
	
	void ChangeState( kBaseState* _state );
	void AddState( kBaseState* _state );
	void RemoveState( kBaseState* _state );
};

#endif