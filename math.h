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
bool isVisible( vec3_t point );

#endif
