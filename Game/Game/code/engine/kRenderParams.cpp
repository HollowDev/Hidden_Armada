#include "kRenderParams.h"

kRenderPass g_RenderPassDebug;

void kRenderParams::InitRenderPasses( void )
{
	g_RenderPassDebug.Initialize( L"assets/effects/basic.fx" );
}