//
//  globals.cpp
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "globals.h"

// routine helper functions

void die(const char* msg)
{
    printf(msg);
    exit(EXIT_FAILURE);
}


vec4_t colorOrange = {1, 0.5, 0, 1};
vec4_t colorOrangeAlpha = {1, 0.5, 0, 0.4};
vec4_t colorBlueAlpha = {0.3, 0.3, 1, 0.5};
vec4_t colorWhite = {1, 1, 1, 1};
vec4_t colorRed = {1, 0, 0, 0.5};
vec4_t colorBlack = {0, 0, 0, 1};