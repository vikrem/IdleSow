//
//  CGui.h
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#ifndef __IdleSow__CGui__
#define __IdleSow__CGui__

#include "globals.h"

class CGui
{
    public:
        CGui();
        void InitSettings();
        void Draw();
        void Shutdown();
        vector<CMenuItem> items;
    private:
        mufont_s *guiFont;
        
};
void GUI_MenuSelect();
void GUI_MoveUp();
void GUI_MoveDown();

extern CGui gGui;

#endif /* defined(__IdleSow__CGui__) */
