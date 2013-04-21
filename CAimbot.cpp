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
    
    
    
    if(config.aimbot.fovenabled)
        DrawRectOutline(pCgs->vidWidth / 2 - config.aimbot.aimfov / 2, pCgs->vidHeight / 2 - config.aimbot.aimfov / 2,
                        config.aimbot.aimfov , config.aimbot.aimfov , 1, colorBlueAlpha);
    
    centity_t *target = NULL; // Store the best target we've seen
    
    float minDist = FLT_MAX; // Maximum representable float
    
    
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
        
        if(!isVisible(pEnt->current.origin))
            continue; // Can't see this person
        
        vec3_t diff = {0, 0, 0};
        VectorSubtract(pCg->view.refdef.vieworg, pEnt->current.origin, diff);
        
        if( VectorLength(diff) < minDist )
        {
            target = pEnt;
            minDist = VectorLength(diff);
        }
    }
    
    
    if(!target)
        return; // Couldn't find a suitable player to aim at
    
    vec3_t dir = {0, 0, 0};
    vec3_t angs = {0, 0, 0};
    vec3_t firefrom = {0, 0, 0};
    vec3_t delta = { 0, 0 , 0};
    vec3_t aimtarget = { 0, 0, 0};
    vec3_t ut = {0, 0, 0};
    
    float dt = 0.0f;
    
    // New lag extrapolation! s = ut + 1/2 a t^2
    
    VectorSubtract(target->current.origin, target->prev.origin, ut);
    
    // uncertain whether the time is really one frame or not, so let's solve for it
    
    if((float)VectorLength(target->prevVelocity) != 0.0f) // Dont div by zero!
        dt = (float)VectorLength(ut) / (float)VectorLength(target->prevVelocity); // change in time between frames
    
    
    VectorSubtract(target->velocity, target->prevVelocity, delta); // A * t

    for(int i = 0; i < 3; i++)
    {
        delta[i] = (float)delta[i] * (float)dt; // a * t^2
        delta[i] *= 0.5f; // 1/2 a t^2
        aimtarget[i] = delta[i] + ut[i] + target->current.origin[i];
    }
    
    // Our own view vector is already lag compensated
    VectorCopy(pCg->view.refdef.vieworg, firefrom);
    
    
    // Subtract vectors
    VectorSubtract(aimtarget, firefrom, dir);
    
    if(!isVisible(aimtarget))
        return; // No hope in aiming at something we can't see
    
    if(config.aimbot.fovenabled)
    {
        vec2_t coords;
        
        
        if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
            return; // This person is not in my view
        
        oImport->R_TransformVectorToScreen(&pCg->view.refdef, aimtarget, coords);
        
        // Only aim in this area.
        
        if (! (coords[0] >= (pCgs->vidWidth / 2 - config.aimbot.aimfov / 2)))
            return;
        if (! (coords[0] <= (pCgs->vidWidth / 2 + config.aimbot.aimfov )))
            return;
        if (! (coords[1] >= (pCgs->vidHeight / 2 - config.aimbot.aimfov / 2)))
            return;
        if (! (coords[1] <= (pCgs->vidHeight / 2 + config.aimbot.aimfov )))
            return;
    }
    
    VecToAngles(dir, angs);
    
    // Toggle this flag between aims and fires
    // to avoid prefire
    if(m_bAiming)
    {
        if(config.aimbot.autoshoot/*&& pCg->pointedNum && !( pCg->frame.playerState.stats[STAT_POINTED_TEAMPLAYER] & 0x1F ) */)
        {
            pCl->cmds[pCl->cmdNum & CMD_MASK].buttons |= BUTTON_ATTACK;
        }
    }
    else
    {
        for(int i = 0; i < 2; i++)
            angs[i] -= pCg->view.angles[i];
        
        for(int i = 0; i < 2; i++)
            pCl->viewangles[i] += angs[i];
    }
    
    m_bAiming = !m_bAiming;

}