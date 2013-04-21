//
//  CAimbot.h
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#ifndef IdleSow_CAimbot_h
#define IdleSow_CAimbot_h

#include "globals.h"

class CAimbot
{
    public:
        CAimbot() : m_bAiming(false) {}
        void DoAim();
    private:
        bool m_bAiming;
};

extern CAimbot gAimbot;


#endif
