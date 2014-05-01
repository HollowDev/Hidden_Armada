#pragma once
#ifndef _MEMORY_MACROS_H_
#define _MEMORY_MACROS_H_

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Helpful memory macros, to make your life easier
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define SAFE_DELETE(x)  if( x ) { delete x;			(x) = nullptr; }
#define SAFE_RELEASE(x) if( x ) { (x)->Release();	(x) = nullptr; }

#endif