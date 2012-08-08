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
    config.aimbot.enabled = TRUE;
    config.aimbot.autoshoot = false;
    config.aimbot.fovenabled = TRUE;
    config.aimbot.aimfov = 30; // Aim within 30 px
    
    config.camera.enabled = false;
    
    config.esp.enabled = TRUE;
    config.esp.espdist = 4096;
    config.esp.name_esp = TRUE;
    config.esp.weapon_esp = TRUE;
    
    // Aimbot off. Camera off. Esp off.
}