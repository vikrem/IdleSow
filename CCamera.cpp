//
//  CCamera.cpp
//  IdleSow
//
//  Created by IX on 2013-04-09.
//
//

#include "globals.h"

CCamera gCamera;

void CCamera::Draw(const refdef_s *fd)
{
    
    if(!config.camera.enabled)
        return;
    
    refdef_t mirrorCam;
    memcpy(&mirrorCam, fd, sizeof(mirrorCam));
    
    mirrorCam.x = 180;
    mirrorCam.y = 51;
    mirrorCam.width = 198;
    mirrorCam.height = 198;
    
    // Reverse camera to point backwards
    
    vec3_t cameraAngles;
    VecToAngles(mirrorCam.viewaxis[0], cameraAngles);
    cameraAngles[YAW] += 180.0f;
    if(cameraAngles[YAW] > 360.0f)
        cameraAngles[YAW] -= 360.0f;
    else if(cameraAngles[YAW] < 0.0f)
        cameraAngles[YAW] += 360.0f;
    
    AnglesToAxis(cameraAngles, mirrorCam.viewaxis);
    
    // Draw reversed camera
    (*orig_R_Renderscene)(&mirrorCam);
    
    
    
}
