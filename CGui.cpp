//
//  CGui.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"

CGui gGui;

void CGui::Draw()
{
    DrawRectFill(20, 20, 100, 200, colorOrangeAlpha);
    DrawRectOutline(20, 20, 100, 200, 1, colorBlack);
}