//
//  math.cpp
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#include "globals.h"


// Convert a vector into view angles
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


void AnglesToAxis( const vec3_t angles, vec3_t axis[3] )
{
	AngleVectors( angles, axis[0], axis[1], axis[2] );
	VectorInverse( axis[1] );
}

void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up )
{
	float angle;
	static float sr, sp, sy, cr, cp, cy, t;
	// static to help MS compiler fp bugs
    
	angle = DEG2RAD( angles[YAW] );
	sy = sin( angle );
	cy = cos( angle );
	angle = DEG2RAD( angles[PITCH] );
	sp = sin( angle );
	cp = cos( angle );
	angle = DEG2RAD( angles[ROLL] );
	sr = sin( angle );
	cr = cos( angle );
    
	if( forward )
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if( right )
	{
		t = sr*sp;
		right[0] = ( -1*t*cy+ -1*cr* -sy );
		right[1] = ( -1*t*sy+ -1*cr*cy );
		right[2] = -1*sr*cp;
	}
	if( up )
	{
		t = cr*sp;
		up[0] = ( t*cy+ -sr* -sy );
		up[1] = ( t*sy+ -sr*cy );
		up[2] = cr*cp;
	}
}

float Q_RSqrt( float number )
{
    int i;
    float x2, y;
    
    if( number == 0.0 )
        return 0.0;
    
    x2 = number * 0.5f;
    y = number;
    i = *(int *) &y;    // evil floating point bit level hacking
    i = 0x5f3759df - ( i >> 1 ); // what the fuck?
    y = *(float *) &i;
    y = y * ( 1.5f - ( x2 * y * y ) ); // this can be done a second time
    
    return y;
}

bool isVisible( vec3_t point )
{
    trace_t t;
    vec3_t vec3_origin = {0, 0, 0};
    oExport->Trace(&t,pCg->view.origin, vec3_origin, vec3_origin,point, -1 , MASK_OPAQUE );
    
    return ( t.fraction == 1.0f );
}
