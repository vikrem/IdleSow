//
//  CAimbot.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"

CAimbot gAimbot;

void CAimbot::DoAim()
{
    if(!config.aimbot.enabled)
        return; // aimbot is disabled
    
    // Loop over all players
    
    for(int i = 0; i < MAX_CLIENTS/*pCg->frame.numEntities*/; i++)
    {
        
        centity_t *pEnt = &(pEnts[i + 1]);
        
        
        if( !pCgs->clientInfo[i].name[0])
            continue;
        if( pEnt->serverFrame != pCg->frame.serverFrame )
            continue;
        
        if( !pEnt->current.modelindex || !pEnt->current.solid ||
           pEnt->current.solid == SOLID_BMODEL || pEnt->current.team == TEAM_SPECTATOR )
            continue;
        
        
        if(i == pCgs->playerNum)
            continue; // Don't shoot ourselves
        
        vec3_t dir = {0, 0, 0};
        vec3_t angs = {0, 0, 0};
        
        VectorSubtract(pEnt->ent.origin, pCg->view.refdef.vieworg, dir);
        
        if(config.aimbot.fovenabled)
        {
            vec2_t coords;
            
            if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
                continue; // This person is not in my view
            
            oImport->R_TransformVectorToScreen(&pCg->view.refdef, pEnt->ent.origin, coords);
            
            // Only aim in this area.
            
            if (! (coords[0] >= (pCgs->vidWidth / 2 - config.aimbot.aimfov)))
                continue;
            if (! (coords[0] <= (pCgs->vidWidth / 2 + config.aimbot.aimfov)))
                continue;
            if (! (coords[1] >= (pCgs->vidHeight / 2 - config.aimbot.aimfov)))
                continue;
            if (! (coords[1] <= (pCgs->vidHeight / 2 + config.aimbot.aimfov)))
                continue;
        }
        
        VecToAngles(dir, angs);
        
        
        for(int i = 0; i < 2; i++)
            angs[i] -= pCg->view.angles[i];
        
        for(int i = 0; i < 2; i++)
            pCl->viewangles[i] += angs[i];
        /*
        // Silly draw code
        vec4_t boxColor = { 1, 0.5, 0, 0.5 };
        oImport->R_DrawStretchPic( 10, 10, 100, 300, 0, 0, 1, 1, boxColor, oImport->R_RegisterPic("gfx/ui/white") );*/
    }
}