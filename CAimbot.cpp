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
    
    // Don't aim if i'm dead, or speccing
    centity_t *me = &(pEnts[pCgs->playerNum + 1]);
    if(!me->current.solid || me->current.team == TEAM_SPECTATOR || me->current.solid == SOLID_BMODEL)
        return;
    
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
        
        
        // Do not consider players that are on my team
        if(me->current.team != TEAM_PLAYERS)
            if(pEnt->current.team == me->current.team)
                continue;
        
        if(i == pCgs->playerNum)
            continue; // Don't shoot ourselves
        
        vec3_t dir = {0, 0, 0};
        vec3_t angs = {0, 0, 0};
        vec3_t target = {0, 0, 0};
        VectorLerp( pEnt->prev.origin, pCg->lerpfrac, pEnt->current.origin, target );
        VectorSubtract(target, pCg->view.refdef.vieworg, dir);
        
        if(config.aimbot.fovenabled)
        {
            vec2_t coords;
            
            if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
                continue; // This person is not in my view
            
            oImport->R_TransformVectorToScreen(&pCg->view.refdef, target, coords);
            
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
        
        // Do aim
        for(int i = 0; i < 2; i++)
            angs[i] -= pCg->view.angles[i];
        
        for(int i = 0; i < 2; i++)
            pCl->viewangles[i] += angs[i];
        //if (pCl->snapShots[pCl->receivedSnapNum].playerState.plrkeys
        if(config.aimbot.autoshoot)
            pCl->cmds[pCl->cmdNum & CMD_MASK].buttons |= BUTTON_ATTACK;
        
    }
}