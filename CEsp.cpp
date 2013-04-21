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

void CEsp::Unload()
{
    espFont = NULL; // Destroy old font
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
        vec3_t target = {0, 0, 0};
        VectorCopy(pEnt->current.origin, target);
        //VectorMA(pEnt->current.origin, pCg->frameTime, pEnt->velocity, target);
        VectorSubtract(target, pCg->view.refdef.vieworg, dir);
        if( DotProduct(dir, pCg->view.axis[FORWARD] ) < 0)
            continue; // This person is not in my view
        
        if( VectorLengthFast(dir) > config.esp.espdist)
            continue; // Person too far
        
        oImport->R_TransformVectorToScreen(&pCg->view.refdef, target, coords);
        
        vec_t x = coords[0];
        vec_t y = coords[1];
        if(config.esp.name_esp)
            oImport->SCR_DrawString((int)coords[0], (int)coords[1], ALIGN_CENTER_TOP, pCgs->clientInfo[i].name, espFont, colorOrange);
        
        if(config.esp.weapon_esp)
            oImport->R_DrawStretchPic(coords[0]-20,coords[1]-20,35, 35,0, 0, 1, 1,colorWhite,(shader_s*)(pCgs->media.shaderWeaponIcon[pEnt->current.weapon - 1])->data);
        
        if(config.esp.box_esp)
        {
            // Draw by team
            int teamNum = pEnt->current.team;
            vec4_t tColor;
            
            tColor[0] = COLOR_R( pCgs->teamColor[teamNum] ) * ( 1.0/255.0 );
            tColor[1] = COLOR_G( pCgs->teamColor[teamNum] ) * ( 1.0/255.0 );
            tColor[2] = COLOR_B( pCgs->teamColor[teamNum] ) * ( 1.0/255.0 );

            tColor[3] = 0.25;
            int width = 20;
            DrawRectFill(x - width/2, y-width / 2, width, width, tColor);
            DrawRectOutline(x - width/2, y-width/2, width, width, 1, colorBlack);
        }
    }
}
