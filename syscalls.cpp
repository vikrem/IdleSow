//
//  syscalls.cpp
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "globals.h"




void* dlopen(const char *path, int mode)
{
    void* ret = (*orig_dlopen)(path, mode);
    if( path != NULL && strstr(path, "/cgame_mac.dylib") != NULL)
    {
        // enumerate loaded images
        int images = _dyld_image_count();
        if(!images)
            die("Couldn't find any images.\n");
        
        for(int i = 0; i < images; i++)
        {
            const char *img_name = _dyld_get_image_name(i);
            unsigned int img_base = 0;
            
            if(!img_name)
                printf("Couldn't read image %d\n", i);
            
            img_base = (unsigned int) _dyld_get_image_header(i);
            
            if(!img_base)
                die("Couldn't get image address.");
            
            if(i == 0) // Main module
            {
                printf("Main module!\n");
                pCl = (client_state_t*)(img_base + OFFSET_CLIENT);
                
            }
            
            if(strstr(img_name, "/cgame_mac.dylib") != NULL)
            {
                printf("Found cgame at 0x%X\n", img_base);

                pCg = (cg_state_t*)(img_base + OFFSET_STATE);
                pCgs = (cg_static_t*)(img_base + OFFSET_STATIC);
                pEnts = (centity_t*)(img_base + OFFSET_ENT);
                oImport = (cgame_import_t*)(img_base + OFFSET_IMP);
                oExport = ((cgame_export_t*)(img_base + OFFSET_EXP));
                
            }
            else if(strstr(img_name, "/game_mac.dylib") != NULL)
                printf("Found client at 0x%X\n", img_base);
                
        }
        fflush(stdout);
    
    }

    return ret;
}
