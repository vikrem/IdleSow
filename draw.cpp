//
//  draw.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"



void DrawRectFill(int x, int y, int w, int h, vec4_t color)
{
    oImport->R_DrawStretchPic( x, y, w, h, 0, 0, 1, 1, color, oImport->R_RegisterPic("gfx/ui/white"));
}

void DrawRectOutline(int x, int y, int w, int h, int borderthickness, vec4_t color)
{
    // Draw the top line
    DrawRectFill( x, y, w, borderthickness, color);
    // Draw left side
    DrawRectFill( x, y, borderthickness, h, color);
    
    // Draw the right side
    DrawRectFill( x + w, y, borderthickness, h, color);
    // Draw the bottom
    DrawRectFill( x, y + h, w, borderthickness, color);
                              
}