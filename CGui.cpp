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
    selection = 0;
    InitSettings();
}

void CGui::Shutdown()
{
    this->guiFont = NULL;
    selection = 0;
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
    items.push_back(fov);
    items.push_back(cam);
    items.push_back(espEnabled);
    items.push_back(nameEsp);
    items.push_back(weapEsp);
    items.push_back(boxEsp);


}

void CGui::Draw()
{
    if(!guiFont)
        guiFont = pCgs->fontSystemSmall;
    
    selection %= items.size();
    selection = abs(selection);
    
    //DrawRectFill(20, 20, 100, 200, colorOrangeAlpha);
    //DrawRectOutline(20, 20, 100, 200, 1, colorBlack);
    // Base of where to draw
    int width = 200;
    int xbase = 10;
    int ybase = 10;
    
    int height = oImport->SCR_strHeight(guiFont);
    
    for(int i = 0; i < items.size(); i++)
    {
        CMenuItem tItem = items[i];
        width = max(oImport->SCR_strWidth(tItem.label, guiFont, 0), width);
        vec4_t textColor = { 0, 0, 0, 1};
        char tLabel[32];
        int bottom = ybase + i * height;
        strcpy(tLabel, tItem.label);
        if (tItem.type == BOOLEAN)
        {
            if( *((bool*)tItem.setting) )
            {
                textColor[1] = 0.7;
                sprintf(tLabel, "%s: ON", tLabel);
            }
            else
            {
                textColor[0] = 0.7;
                sprintf(tLabel, "%s: OFF", tLabel);
            }
        }
        else
        {
            textColor[0] = textColor[1] = textColor[2] = 1;
            sprintf(tLabel, "%s: %d", tLabel, *((int*)tItem.setting));

        }
        
        // Draw background for entry
        DrawRectFill(xbase, bottom, width, height, colorOrangeAlpha);
        WriteText(xbase, bottom, tLabel, ALIGN_LEFT_TOP, 0, guiFont, textColor);
        DrawRectOutline(xbase, bottom, width, height, 1, colorWhite);
    }
}












