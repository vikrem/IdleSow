//
//  globals.h
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef IdleSow_globals_h
#define IdleSow_globals_h

#include <stdlib.h>
#include <stdarg.h>
//#define __USE_GNU

// This definition hits up certain things inside the engine headers that have been modified
// in order to make things nicely compile.
#define HAX

#include <stdio.h>
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <float.h>

using namespace std;



#include "../../../SDK/warsow_1.02_sdk/source/cgame/cg_local.h"

#include "../../../SDK/warsow_1.02_sdk/source/client/client.h"
#include "../../../SDK/warsow_1.02_sdk/source/ref_gl/r_local.h"
#include "../../../SDK/warsow_1.02_sdk/source/gameshared/q_math.h"


#include "libMain.h"
#include "hooks.h"
#include "settings.h"
#include "syscalls.h"
#include "CMenuItem.h"
#include "math.h"
#include "CAimbot.h"
#include "CCamera.h"
#include "CEsp.h"
#include "CGui.h"
#include "draw.h"


void die(const char* msg);

extern vec4_t colorOrangeAlpha;
extern vec4_t colorBlueAlpha;
#endif
