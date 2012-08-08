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
    
    for(int i = 0; i < MAX_CLIENTS/*pCg->frame.numEntities*/; i++)
    {
        centity_t *pEnt = &(pEnts[i + 1]);
        vec2_t coords;
        vec4_t colorOrange = {1, 0.5, 0, 1};
        vec4_t colorWhite = {1, 1, 1, 1};
        if( !pCgs->clientInfo[i].name[0])
            continue;
        if( pEnt->serverFrame != pCg->frame.serverFrame )
            continue;
        if( !pEnt->current.modelindex || !pEnt->current.solid ||
           pEnt->current.solid == SOLID_BMODEL || pEnt->current.team == TEAM_SPECTATOR )
            continue;
        
        
        if(i == pCgs->playerNum)
            continue;
        vec3_t dir = {0, 0, 0};
        vec3_t angs;
        VectorSubtract(pEnt->ent.origin, pCg->view.refdef.vieworg, dir);
        if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
            continue;
        oImport->R_TransformVectorToScreen(&pCg->view.refdef, pEnt->ent.origin, coords);
        
        
        //coords[1];// = pCgs->vidHeight - coords[1];
        oImport->SCR_DrawString((int)coords[0], (int)coords[1], ALIGN_CENTER_TOP, pCgs->clientInfo[i].name, oImport->SCR_RegisterFont("bitdust_16")/*pCgs->fontSystemSmall*/, colorOrange);
        oImport->R_DrawStretchPic(coords[0]-20,coords[1]-20,35, 35,0, 0, 1, 1,colorWhite,(shader_s*)(pCgs->media.shaderWeaponIcon[pEnt->current.weapon - 1])->data);
        
        VecToAngles(dir, angs);
        
        
        for(int i = 0; i < 2; i++)
            /*pCl->viewangles[i] += */ angs[i] -= pCg->view.angles[i];

        for(int i = 0; i < 2; i++)
            pCl->viewangles[i] += angs[i];
        // Silly draw code
        vec4_t boxColor = { 1, 0.5, 0, 0.5 };
        oImport->R_DrawStretchPic( 10, 10, 100, 300, 0, 0, 1, 1, boxColor, oImport->R_RegisterPic("gfx/ui/white") );
    }
    
}

void hk_R_AddEntityToScene(const struct entity_s* ent)
{
    entity_s* w_ent = (entity_s*)ent;
    w_ent->renderfx |= EF_GODMODE;
    (*orig_R_AddEntityToScene)(ent);
}

void hk_RenderView( float frameTime, float realFrameTime, int realTime, unsigned int serverTime, float stereo_separation, unsigned int extrapolationTime )
{
    (*orig_RenderView)(frameTime, realFrameTime, realTime, serverTime, stereo_separation, extrapolationTime);
}

void VecToAngles( const vec3_t vec, vec3_t angles )
{
	float forward;
	float yaw, pitch;
    
	if( vec[1] == 0 && vec[0] == 0 )
	{
		yaw = 0;
		if( vec[2] > 0 )
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if( vec[0] )
			yaw = RAD2DEG( atan2( vec[1], vec[0] ) );
		else if( vec[1] > 0 )
			yaw = 90;
		else
			yaw = -90;
		if( yaw < 0 )
			yaw += 360;
        
		forward = sqrt( vec[0]*vec[0] + vec[1]*vec[1] );
		pitch = RAD2DEG( atan2( vec[2], forward ) );
		if( pitch < 0 )
			pitch += 360;
	}
    
	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
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







