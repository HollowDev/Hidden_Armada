#include "kGameObject.h"
#include "kComponent.h"
#include "kTransformComponent.h"

#include "memory_macros.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kGameObject::kGameObject( void )
{
	m_Type = RTTI_kGameObject;

	m_Parent = nullptr;
	m_Transform = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
kGameObject::~kGameObject( void )
{
	Release();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Releases all the data inside of this game object
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Release( void )
{
	for( unsigned int i = 0; i < m_Components.size(); ++i ) SAFE_DELETE( m_Components[i] );
	for( unsigned int i = 0; i < m_Children.size(); ++i ) SAFE_DELETE( m_Children[i] );

	m_Components.clear();
	m_Children.clear();

	m_Parent = nullptr;
	m_Transform = nullptr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the game object
Params:
	_timer - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Update( float _timer )
{
	// TODO:: Push the transform onto the k2DFoundationStack
	UpdateChildren( _timer );
	UpdateComponents( _timer );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the children belonging to this kGameObject
Params:
	_timer - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::UpdateChildren( float _timing )
{
	vector< kGameObject* >::iterator iter = m_Children.begin();
	for( iter; iter != m_Children.end(); ++iter )
	{
		(*iter)->Update( _timing );
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Updates the components belonging to this kGameObject
Params:
	_timer - the time that has passed since the last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::UpdateComponents( float _timing )
{
	vector< kComponent* >::iterator iter = m_Components.begin();
	for( iter; iter != m_Components.end(); ++iter )
	{
		(*iter)->Update( _timing );
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Docks a child to this kGameObject
Params:
	_child - the child to dock
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Dock( kGameObject* _child )
{
	_child->SetParent( this );
	m_Children.push_back( _child );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Docks a component to this kGameObject
Params:
	_component - the component to dock
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Dock( kComponent* _component )
{
	_component->SetOwner( this );
	m_Components.push_back( _component );

	if( _component->GetType() == RTTI_kTransformComponent )
		m_Transform = (kTransformComponent*)_component;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Undocks a child from this kGameObject
Params:
	_child - the child to undock
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Undock( kGameObject* _child )
{
	vector< kGameObject* > alive;
	for( unsigned int i = 0; i < m_Children.size(); ++i )
	{
		if( m_Children[i] != _child )
			alive.push_back( m_Children[i] );
	}

	m_Children.clear();
	m_Children = alive;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Undocks a component from this kGameObject
Params:
	_component - the component to undock
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void kGameObject::Undock( kComponent* _component )
{
	vector< kComponent* > alive;
	for( unsigned int i = 0; i < m_Components.size(); ++i )
	{
		if( m_Components[i] != _component )
			alive.push_back( m_Components[i] );
	}

	m_Components.clear();
	m_Components = alive;
}
