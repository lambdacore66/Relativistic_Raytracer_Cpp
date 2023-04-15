// 'ray' class definition based on the parametric 3D line equation P(t) = A+B*t

#ifndef RAY_H
#define RAY_H

// Loads the vec3 class code to use vectors
#include "vec3.h"

class ray {
	public:
		
		vec3 orig; vec3 dir;
		ray(vec3 origin = vec3(0,0,0), vec3 direction = vec3(1,0,0)) { orig = origin; dir = direction;}
		
		// Obtains A and B as vectors
		vec3 origin() {return orig; }
		vec3 direction() {return dir;}
		
		// Obtains P(t) as 'ray::at(t)'
		vec3 at(double t);

};

// Obtains P(t) as 'ray::at(t)'
vec3 ray::at(double t) {return orig + t*dir;}

#endif
