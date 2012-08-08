//
//  CEsp.h
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#ifndef IdleSow_CEsp_h
#define IdleSow_CEsp_h

#include "globals.h"

class CEsp
{
    public:
        CEsp();
        void DoESP();
        void Unload();
    private:
        mufont_s* espFont;
};

extern CEsp gEsp;

#endif
