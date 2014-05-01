#pragma once
#ifndef _RENDER_PARAMS_H_
#define _RENDER_PARAMS_H_

#include "kRenderPass.h"

extern kRenderPass g_RenderPassDebug;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Handles the construction of all the kRenderPasses
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kRenderParams
{
public:
	static void InitRenderPasses( void );
};

#endif