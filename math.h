//
//  math.h
//  IdleSow
//
//  Created by IX on 2012-08-08.
//
//

#ifndef IdleSow_math_h
#define IdleSow_math_h

// Convert a vector into view angles
void VecToAngles( const vec3_t vec, vec3_t angles );
float Q_RSqrt( float number );
void AnglesToAxis( const vec3_t angles, vec3_t axis[3] );
void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up );

bool isVisible( vec3_t point );

#endif
