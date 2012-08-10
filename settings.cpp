//
//  settings.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"

// global configuration
settings_t config;

// default config

void set_default_settings()
{
    // set default options
    config.aimbot.enabled = false;
    config.aimbot.autoshoot = false;
    config.aimbot.fovenabled = false;
    config.aimbot.aimfov = 30; // Aim within 30 px
    
    config.camera.enabled = false;
    
    config.esp.enabled = TRUE;
    config.esp.espdist = 4096;
    config.esp.name_esp = TRUE;
    config.esp.weapon_esp = FALSE;//TRUE;
    config.esp.box_esp = TRUE;
    
    config.menu.selection = 0;
    
    // Aimbot off. Camera off. Esp off.
}