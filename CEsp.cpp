//
//  CEsp.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"

// define global
CEsp gEsp;


CEsp::CEsp()
{
    espFont = NULL;//oImport->SCR_RegisterFont("bitdust_16");
}

void CEsp::DoESP()
{
    if(!config.esp.enabled)
        return;
    if(!espFont)
        espFont = oImport->SCR_RegisterFont("bitdust_16");
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
            continue; // Don't ESP ourselves
        
        vec3_t dir = {0, 0, 0};
        
        VectorSubtract(pEnt->ent.origin, pCg->view.refdef.vieworg, dir);
        if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
            continue; // This person is not in my view
        
        if( VectorLengthFast(dir) > config.esp.espdist)
            continue; // Person too far
        
        oImport->R_TransformVectorToScreen(&pCg->view.refdef, pEnt->ent.origin, coords);
        
        
        if(config.esp.name_esp)
            oImport->SCR_DrawString((int)coords[0], (int)coords[1], ALIGN_CENTER_TOP, pCgs->clientInfo[i].name, espFont, colorOrange);
        
        if(config.esp.weapon_esp)
            oImport->R_DrawStretchPic(coords[0]-20,coords[1]-20,35, 35,0, 0, 1, 1,colorWhite,(shader_s*)(pCgs->media.shaderWeaponIcon[pEnt->current.weapon - 1])->data);
        
    }
}
