//
//  hooks.h
//  IdleSow
//
//  Created by IX on 12-08-04.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef IdleSow_hooks_h
#define IdleSow_hooks_h

#include "globals.h"

extern cg_state_t *pCg;// = NULL;
extern cg_static_t *pCgs;// = NULL;
extern centity_t* pEnts;// = NULL;

extern client_state_t *pCl;// = NULL;

// Engine functions
extern cgame_import_t *oImport;// = NULL;
extern cgame_export_t *oExport;// = NULL;

// offsets!
// Some of these are relative to where dyld loads Warsow itself (client and exports), others are to cgame.

#define OFFSET_STATE 0x19A3D4 // Correct from the beginning
#define OFFSET_STATIC 0x312194 // Fixed
#define OFFSET_ENT 0x224074 // Probably fixed
#define OFFSET_IMP 0x17E938 // Updated for Wsw 1.02. No idea why this changed
#define OFFSET_EXP 0x35ED50 // Longshot? Unknown if working
#define OFFSET_CLIENT 0x6301f8 // Fixed

void start_hook();

// R_RenderScene
extern void (*orig_R_Renderscene) ( const struct refdef_s *fd);// = NULL;
void hk_R_RenderScene(const struct refdef_s *fd);

// R_AddEntityToScene
extern void (*orig_R_AddEntityToScene) (const struct entity_s *ent);// = NULL;
void hk_R_AddEntityToScene(const struct entity_s* ent);

// RenderView
extern void ( *orig_RenderView )( float frameTime, float realFrameTime, int realTime, unsigned int serverTime, float stereo_separation, unsigned int extrapolationTime );// = NULL;
void hk_RenderView( float frameTime, float realFrameTime, int realTime, unsigned int serverTime, float stereo_separation, unsigned int extrapolationTime );

// Shutdown
extern void (*orig_Shutdown)();
void hk_Shutdown();


#endif
