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


class plane : public hittable {
	
	public:
				
		vec3 n; double C; vec3 Rpos; double Omega1; double Omega2; vec3 speed; color col; vec3 e2; vec3 e3;
	
		plane(vec3 normal = vec3(0,0,1), double K = 0, vec3 pos = vec3(0,0,0), double O1 = 0.0, double O2 = 0.0, vec3 v = vec3(0,0,0), color col1 = color(1, 1, 1)) { 
			
			n = normal.normalize(); C = K; Rpos = pos; Omega1 = O1; Omega2 = O2; speed = v; col = col1;
			
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
		
		hit getHit(ray r) override;
		

};

hit plane::getHit(ray r) {

    ray r_plane = r.LorentzBoost(speed).rotate(Rpos, -Omega1*vec3(0,0,1)).rotate(Rpos, -Omega2*vec3(1,0,0));


	// Rotations DEBUG CODE=========================

	/* if (col.y() == 0.0) {

		r_plane.rotate(Rpos, Omega2*vec3(1,0,0)).rotate(Rpos, Omega1*vec3(0,0,1)).LorentzBoost(-speed).origin().print();
		std::cout << " = ";
		r.origin().print();

		std::cout << "\n";

		r_plane.rotate(Rpos, Omega2*vec3(1,0,0)).rotate(Rpos, Omega1*vec3(0,0,1)).LorentzBoost(-speed).direction().print();
		std::cout << " = ";
		r.direction().print();;

		std::cout << "\n ----------------------------- \n";

	} */

	//==============================================  It seems that the inverse formula works alright for all cases



	
    vec3 rdir = r_plane.direction();
    
	double A = rdir.dot(n);

	if (A == 0) {
		return hit(false, vec4(), rdir);
	}

	double t = (C-r_plane.origin().spatials().dot(n))/A;

    if (t <= 0) {
		return hit(false, vec4(), rdir);
	}

	vec3 pos = r_plane.at(t/c);

    double Pu = pos.dot(e2);
    double Pv = pos.dot(e3);
    
    double coeff1 = 1.0;
	//TEMPORARY
	if (cos(2*pi*Pu)*sin(2*pi*Pv) > 0) {
		coeff1 = 0.66;
	}

	double coeff2 = sqrt((A*A+0.1)/1.1);

    color hit_color = coeff1*coeff2*col;

	pos = (pos-Rpos).rotate(Omega2*vec3(1,0,0)).rotate(Omega1*vec3(0,0,1))+Rpos;
	rdir = rdir.rotate(Omega2*vec3(1,0,0)).rotate(Omega1*vec3(0,0,1));

	// It seems that rotations are not working properly even if Omega1 = Omega2 = 0.0. Time is messed up but somehow for c >> v it works again.
	// Try to see if R is the identity for Omega1 = Omega2 = 0.0 and if it works by just using ONE rotation angle and not the other
	// This needs to be fixed as it happens with all objects. It breaks hits' heriarchy.

	// THE PROBLEM SEEMS TO BE THAT THIS KIND OF ROTATION DOES NOT PRESERVER DISTANCES UNLESS THEY ARE RELATIVE OR MEASURED FROM THE ROTATION POINT

    return hit(true, vec4(pos.x(), pos.y(), pos.z(), r_plane.origin().ptime()-t/c).Lorentz(-speed), rdir, hit_color);
    
	
}

#endif // End of ifndef
