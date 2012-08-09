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
    private:
        mufont_s *guiFont;
        vector<CMenuItem> items;
        int selection;
};


extern CGui gGui;

#endif /* defined(__IdleSow__CGui__) */
