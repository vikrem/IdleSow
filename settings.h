//
//  settings.h
//  IdleSow
//
//  Created by IX on 2012-08-07.
//
//

#ifndef IdleSow_settings_h
#define IdleSow_settings_h

// Settings for aimbot
struct aimbot_settings_t
{
    bool enabled;
    int aimfov;
    bool fovenabled;
    bool autoshoot;
};

// Settings for esp
struct esp_settings_t
{
    bool enabled;
    bool name_esp;
    bool weapon_esp;
    bool box_esp;
    int espdist;
};

// Settings for camera
struct camera_settings_t
{
    bool enabled;
};

struct menu_settings_t
{
    int selection; // selected item
};

struct settings_t
{
    aimbot_settings_t aimbot;
    esp_settings_t esp;
    camera_settings_t camera;
    menu_settings_t menu;
};


// global configuration
extern settings_t config;

void set_default_settings();

#endif
