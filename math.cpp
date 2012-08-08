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
