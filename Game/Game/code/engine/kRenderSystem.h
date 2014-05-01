#pragma once
#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include <vector>
using std::vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Description: Wrapper that renders all of the kRenderPasses that exist.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kRenderPass;
class kRenderSystem
{
	vector< kRenderPass* > m_RenderPasses;

public:
	kRenderSystem( void );
	~kRenderSystem( void );
	
	void Initialize( void );
	void Render( void );
};

extern kRenderSystem g_RenderSystem;

#endif