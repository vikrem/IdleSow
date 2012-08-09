//
//  CGui.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"

CGui gGui;

CGui::CGui()
{
    this->guiFont = NULL;
}

void CGui::InitSettings()
{
    if(items.size() > 1)
        return;
    
    CMenuItem aimbotEnabled("Aimbot", BOOLEAN, &config.aimbot.enabled);
    CMenuItem autoShoot("AutoShoot", BOOLEAN, &config.aimbot.autoshoot);
    CMenuItem fovB("Aim FOV", BOOLEAN, &config.aimbot.fovenabled);
    CMenuItem fov("Aim FOV", INTEGER, &config.aimbot.aimfov);
    
    CMenuItem cam("MirrorCam", BOOLEAN, &config.camera.enabled);
    
    CMenuItem espEnabled("ESP", BOOLEAN, &config.esp.enabled);
    
    CMenuItem nameEsp("Name ESP", BOOLEAN, &config.esp.name_esp);
    
    CMenuItem weapEsp("Weapon ESP", BOOLEAN, &config.esp.weapon_esp);
    
    CMenuItem boxEsp("Box ESP", BOOLEAN, &config.esp.box_esp);
    
    items.push_back(aimbotEnabled);
    items.push_back(autoShoot);
    items.push_back(fovB);
    items.push_back(cam);
    items.push_back(espEnabled);
    items.push_back(nameEsp);
    items.push_back(weapEsp);
    items.push_back(boxEsp);


}

void CGui::Draw()
{
    if(!guiFont)
        guiFont = oImport->SCR_RegisterFont("font/bitdust_16");
    
    DrawRectFill(20, 20, 100, 200, colorOrangeAlpha);
    DrawRectOutline(20, 20, 100, 200, 1, colorBlack);
}