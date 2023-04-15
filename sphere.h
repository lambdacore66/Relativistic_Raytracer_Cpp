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


class sphere: public hittable {
	
	public:
				
		// Parametrized constructor. Orientation is the camera plane angle from the vertical up position.
		vec3 position; vec3 speed; double radius; color col;
	
		sphere(vec3 pos = vec3(), vec3 v = vec3(), double ra = 1, color col1 = color(1, 0, 0)) { 
		
			position = pos; speed = v; radius = ra; col = col1;

		}
		
		hit getHit(ray r) override;
		

};

hit sphere::getHit(ray r) {

	ray r_sph = r.LorentzBoost(speed);

	//ray r_sph = r;
	
	vec3 n = r_sph.direction();
	vec3 delta = r_sph.origin().spatials()-position;
	
	double K2 = 2*n.dot(delta);
	double K3 = delta.norm2() - radius*radius;
	
	double discriminant = K2*K2-4*K3;
	
	if (discriminant < 0) {
		return hit(false, vec4(), vec3());
	}
	
	double t1 = (-K2+sqrt(discriminant))/(2*c);
	double t2 = (-K2-sqrt(discriminant))/(2*c);

	if (t1 < 0) { //BOTH ARE NEGATIVE (t2 < t1)
		return hit(false, vec4(), vec3());
	}


	double t;
	if (t2 < 0) { //t1 is POSITIVE and t2 is NEGATIVE
		t = t2;
	}
	else { //t1 adn t2 are POSITIVE
		t = std::min(t1, t2);
	}

	vec3 pos = r_sph.at(t);

	vec3 coord = (r_sph.at(t) - position).normalize();
	vec3 coordxy = (coord-coord.z()*vec3(0,0,1)).normalize();

	double theta = acos(coord.dot(vec3(0,0,1)));
	double phi = acos(coordxy.x());

	double p = coord.dot(n);
	double coeff1 = sqrt((p*p+0.1)/1.1);

	// FIX CHECKERBOARD
	double coeff2;
	if (sin(6*theta)*cos(6*phi) > 0.0) {
		coeff2 = 1.0;
	} 
	else {
		coeff2 = 0.6;
	} 
	
	color hit_color = coeff1*coeff2*col;

	return hit(true, vec4(pos.x(), pos.y(), pos.z(), r_sph.origin().ptime()-t).Lorentz(-speed), n, hit_color);

	
}
	

#endif // End of ifndef
