#pragma once
#ifndef _WINDOWS_H_
#define _WINDOWS_H_

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Exclude rarely-used stuff from Windows headers
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define WIN32_LEAN_AND_MEAN		    
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>

#endif