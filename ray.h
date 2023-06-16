// 'ray' class definition based on the parametric 3D line equation P(t) = A+B*t

#ifndef RAY_H
#define RAY_H

// Loads the vec3 class code to use vectors
#include "vec3.h"

class ray {
	public:
		
		vec4 orig; vec3 dir;
		ray(vec4 origin = vec4(0,0,0,0), vec3 direction = vec3(1,0,0)) { orig = origin; dir = direction.normalize();}
		
		// Obtains A and B as vectors
		vec4 origin() {return orig; }
		vec3 direction() {return dir;}
		
		// Obtains P(t) as 'ray::at(t)'
		vec3 at(double t);

		ray GalileoBoost(vec3 v);
		ray LorentzBoost(vec3 v);

		ray translate(vec3 Dr);
		ray rotate(vec3 pos, vec3 Omega);

};

// Obtains P(t) as 'ray::at(t)'
vec3 ray::at(double t) {return orig.spatials() + c*t*dir;}

ray ray::GalileoBoost(vec3 v) {
	
	return ray(orig-vec4(0,0,0,0), (-v+c*dir).normalize());

}

ray ray::LorentzBoost(vec3 v) {
	
	return ray(orig.Lorentz(v), speedAddition(v, c*dir)/c); //-((-v)%(-c))

}

ray ray::translate(vec3 Dr) {
	
	return ray(orig+vec4(Dr.x(), Dr.y(), Dr.z(), 0), dir);

}

ray ray::rotate(vec3 pos, vec3 Omega) {

	vec3 rp = (orig.spatials()-pos).rotate(Omega)+pos;
	vec3 dirp = dir.rotate(Omega);
	
	return ray(vec4(rp.x(), rp.y(), rp.z(), orig.ptime()), dirp);

}



#endif
