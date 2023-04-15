// 2-Sphere class definition (3D)
#ifndef SPHERE_H        // Checks if the header 'SPHERE_H' is already defined
#define SPHERE_H        // if not, defines it.


#include <cmath>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "hit.h"


class sphere {
	
	public:
				
		// Parametrized constructor. Orientation is the camera plane angle from the vertical up position.
		vec4 position; vec3 speed; double radius; color col; double time; vec3 s;
	
		sphere(vec4 pos = vec4(), vec3 v = vec3(), double ra = 1, color c = color(255, 0, 0)) { 
		
			position = pos; speed = v; radius = ra; col = c;
		
			time = pos.ptime();
			s = pos.spatials();

		}
		
		hit getHit(ray r);
		color getColor(ray r, hit rayhit);
		

};

hit sphere::getHit(ray r) {
	
	vec3 n = r.direction();
	vec3 delta = r.origin()-s;
	
	double K1 = c*c;
	double K2 = 2*c*n.dot(delta);
	double K3 = delta.norm2() - radius*radius;
	
	double discriminant = K2*K2-4*K1*K3;
	
	if (discriminant < 0) {
		return hit(false, vec4());
	}
	
	double t1 = (-K2+sqrt(discriminant))/(2*K1);
	double t2 = (-K2+sqrt(discriminant))/(2*K1);
	
	double t = std::min(t1, t2);
	vec3 pos = r.at(t);
	
	return hit(true, vec4(pos.x(), pos.y(), pos.z(),t));
	
}

color sphere::getColor(ray r, hit rayhit) {
	
	vec3 n = rayhit.getWhere().spatials()-s;
	n = n.normalize();
	
	double coeff = (n.dot(r.direction())*n.dot(r.direction())+0.1)/1.1;

	return coeff*col;
}

#endif // End of ifndef
