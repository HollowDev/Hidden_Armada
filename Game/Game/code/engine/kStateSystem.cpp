#include "kStateSystem.h"
#include "kBaseState.h"
#include "kWinApp.h"

#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kStateSystem::kStateSystem( void )
{
	m_App = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kStateSystem::~kStateSystem( void )
{
	Release();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Initializes the kStateSystem
Params:
	_winApp - pointer to the main application
	_state - the state to start with
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::Initialize( kWinApp* _winApp, kBaseState* _state )
{
	m_App = _winApp;
	m_ToChange = _state;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Releases all the data inside of the kStateSystem
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::Release( void )
{
	SAFE_DELETE(m_ToChange);
	for( unsigned int i = 0; i < m_States.size(); ++i ) SAFE_DELETE(m_States[i]);
	for( unsigned int i = 0; i < m_ToAdd.size(); ++i ) SAFE_DELETE(m_ToAdd[i]);
	for( unsigned int i = 0; i < m_ToRemove.size(); ++i ) SAFE_DELETE(m_ToRemove[i]);

	m_States.clear();
	m_ToAdd.clear();
	m_ToRemove.clear();

	m_App = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the current states
Params:
	_timing - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::Update( float _timing )
{
	ProcessChanges();

	for( unsigned int i = 0; i < m_States.size(); ++i ) 
	{
		m_States[i]->Update( _timing );
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Calls all of the process functions to update the current states, m_States
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::ProcessChanges( void )
{
	ProcessToChange();
	ProcessToAdd();
	ProcessToRemove();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Changes to a specific state, if applicable
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::ProcessToChange( void )
{
	if( m_ToChange )
	{
		for( unsigned int i = 0; i < m_States.size(); ++i ) SAFE_DELETE(m_States[i]);
		m_States.clear();

		m_ToChange->Initialize(m_App);
		m_States.push_back(m_ToChange);
		m_ToChange = nullptr;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Adds the specified states to the main state list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::ProcessToAdd( void )
{
	if( m_ToAdd.size() > 0 )
	{
		for( unsigned int i = 0; i < m_ToAdd.size(); ++i )
		{
			m_ToAdd[i]->Initialize(m_App);
			m_States.push_back(m_ToAdd[i]);
		}
		m_ToAdd.clear();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Removes the specified states from the main state list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::ProcessToRemove( void )
{
	if( m_ToRemove.size() > 0 )
	{
		for( unsigned int i = 0; i < m_ToRemove.size(); ++i )
		{
			for( unsigned int j = 0; j < m_States.size(); ++j )
			{
				if( m_States[j] == m_ToRemove[i] )
				{
					m_States.erase(m_States.begin() + j);
					j--;
				}
			}
		}
		m_ToRemove.clear();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Sets the state to change to
Params:
	_state - the state to change to
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::ChangeState( kBaseState* _state )
{
	m_ToChange = _state;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Adds a state to add to the main state list
Params:
	_state - the state to add to the main state list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::AddState( kBaseState* _state )
{
	m_ToAdd.push_back( _state );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Adds a state to remove from the main state list
Params:
	_state - the state to remove from the main state list
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kStateSystem::RemoveState( kBaseState* _state )
{
	m_ToRemove.push_back( _state );
}
