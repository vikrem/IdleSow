//
//  hooks.cpp
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "globals.h"

cg_state_t *pCg = NULL;
cg_static_t *pCgs = NULL;
centity_t* pEnts = NULL;

client_state_t *pCl = NULL;

// Engine functions
cgame_import_t *oImport = NULL;
cgame_export_t *oExport = NULL;

void (*orig_R_Renderscene) ( const struct refdef_s *fd) = NULL;

// R_AddEntityToScene
void (*orig_R_AddEntityToScene) (const struct entity_s *ent) = NULL;

// RenderView
void ( *orig_RenderView )( float frameTime, float realFrameTime, int realTime, unsigned int serverTime, float stereo_separation, unsigned int extrapolationTime ) = NULL;

// Shutdown
void (*orig_Shutdown)() = NULL;

void VecToAngles( const vec3_t vec, vec3_t angles );




void start_hook()
{
    // All pointers and structs are up-to-date here.
    oImport->Print("^9Initializing IdleSow...\n");
 
   
    // Apply hooks
    
    // Hook Renderscene
	orig_R_Renderscene = oImport->R_RenderScene;
	oImport->R_RenderScene = &hk_R_RenderScene;
    oImport->Print("^9[+] R_RenderScene hooked\n");
    
	// Hook AddEntity
	orig_R_AddEntityToScene = oImport->R_AddEntityToScene;
	oImport->R_AddEntityToScene = hk_R_AddEntityToScene;
    oImport->Print("^9[+] R_AddEntityToScene hooked\n");
    
	// Hook RenderView
	orig_RenderView = oExport->RenderView;
	oExport->RenderView = &hk_RenderView;
    
    // Hook Shutdown to rerun agent
    orig_Shutdown = oExport->Shutdown;
    oExport->Shutdown = &hk_Shutdown;
    
    oImport->Print("^9[+] RenderView hooked\n");
    
    oImport->Print("^9***************************************************\n");
    oImport->Print("^9If you are seeing this message, all systems are go.\n");
    oImport->Print("^9***************************************************\n");

}

void hk_R_RenderScene(const struct refdef_s *fd)
{
    
    (*orig_R_Renderscene)(fd);

    gEsp.DoESP();
    gAimbot.DoAim();

    
}

void hk_R_AddEntityToScene(const struct entity_s* ent)
{
    (*orig_R_AddEntityToScene)(ent);
}

void hk_RenderView( float frameTime, float realFrameTime, int realTime, unsigned int serverTime, float stereo_separation, unsigned int extrapolationTime )
{
    (*orig_RenderView)(frameTime, realFrameTime, realTime, serverTime, stereo_separation, extrapolationTime);
}



void hk_Shutdown()
{
    // Release info
    oImport = NULL;
    oExport = NULL;
    pCg = NULL;
    pCgs = NULL;
    pEnts = NULL;
    
    start_agent();
    (*orig_Shutdown)();
}







