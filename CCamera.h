//
//  CCamera.h
//  IdleSow
//
//  Created by IX on 2013-04-09.
//
//

#ifndef __IdleSow__CCamera__
#define __IdleSow__CCamera__

#include "globals.h"

class CCamera
{
    public:
        void Draw(const refdef_s *fd); // Draw rear view camera
    
};

extern CCamera gCamera;

#endif /* defined(__IdleSow__CCamera__) */

