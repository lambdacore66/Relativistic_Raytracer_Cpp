// Infinite plane class definition
#ifndef PLANE_H        // Checks if the header 'PLANE_H' is already defined
#define PLANE_H        // if not, defines it.


#include <cmath>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "hit.h"


class plane {
	
	public:
				
		vec3 n; double C; color col; vec3 e2; vec3 e3;
	
		plane(vec3 normal = vec3(0,0,1), double K = 0, color col1 = color(1, 1, 1)) { 
		
			n = normal.normalize(); C = K; col = col1;

			// Orthogonal trihedra
            if (n.cross(vec3(0,0,1)).norm() <= 1E-10) {
                e2 = vec3(1,0,0);
                e3 = vec3(0,1,0);
            }
            else {
                e2 = n.cross(vec3(0,0,1)).normalize();      // "Horizontal" direction on the rectangle plane. Unit vector
			    e3 = e2.cross(n).normalize(); 		        // "Vertical" direction on the rectangle plane. Unit vector
            }

		}
		
		hit getHit(ray r);
		

};

hit plane::getHit(ray r) {
	
	vec3 rdir = r.direction();

	double A = rdir.dot(n);

	if (A == 0) {
		return hit(false, vec4(), rdir);
	}

	double t = (C+r.origin().spatials().dot(n))/A;

	if (t > 0){
		return hit(false, vec4(), rdir);
	}

	vec3 hitpos = r.at(t*c);

    double Pu = hitpos.dot(e2);
    double Pv = hitpos.dot(e3);

    double coeff1 = 1.0;

	if (cos(0.5*pi*Pu)*sin(0.5*pi*Pv) > 0) {

		coeff1 = 0.66;

	}

	double coeff2 = sqrt((A*A+0.1)/1.1);

    color hit_color = coeff1*coeff2*col;
	return hit(true, vec4(hitpos.x(), hitpos.y(), hitpos.z(), t), rdir, hit_color);
	
}

#endif // End of ifndef
