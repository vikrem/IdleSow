//
//  CMenuItem.h
//  IdleSow
//
//  Created by IX on 2012-08-09.
//
//

#ifndef __IdleSow__CMenuItem__
#define __IdleSow__CMenuItem__

#include "globals.h"

enum CMenuItemType { BOOLEAN, INTEGER }; // What kind of setting

struct CMenuItem
{
    CMenuItem( const char* label, CMenuItemType item, void* setting) : label(label), type(type), setting(setting) {}
    const char* label; // Name of setting
    CMenuItemType type; // Type of setting
    void* setting; // Pointer to modify setting
    
};

#endif /* defined(__IdleSow__CMenuItem__) */
