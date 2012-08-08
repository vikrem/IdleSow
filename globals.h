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
#define HAX
#include <stdio.h>
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


void die(const char* msg);

#include "../../../SDK/warsow_1.0_sdk/source/cgame/cg_local.h"

#include "../../../SDK/warsow_1.0_sdk/source/client/client.h"
#include "../../../SDK/warsow_1.0_sdk/source/ref_gl/r_local.h"
#include "../../../SDK/warsow_1.0_sdk/source/gameshared/q_math.h"


#include "libMain.h"
#include "hooks.h"
#include "settings.h"
#include "syscalls.h"
#include "math.h"
#include "CAimbot.h"
#include "CEsp.h"
#include "draw.h"


#endif
