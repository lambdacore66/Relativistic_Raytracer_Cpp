#ifndef RECTANGLE_H        // Checks if the header 'RECTANGLE_H' is already defined
#define RECTANGLE_H        // if not, defines it.


#include <cmath>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "hit.h"
#include "plane.h"


class rectangle : public hittable {
	
	public:

		// rectangles are defined by the center position, its normal vector n and a rotation angle phi around that vector. 	
		vec3 position; vec3 speed; vec3 n; double Omega; double X; double Y; color col;

        vec3 e2; vec3 e3;
	
		rectangle(vec3 pos = vec3(0,0,0), vec3 v = vec3(0,0,0), vec3 normal = vec3(0,0,1), double O = 0.0, double x = 1.0, double y = 1.0, color col1 = color(1, 1, 1)) { 
		
			position = pos; speed = v; n = normal.normalize(); Omega = O;  X = abs(x),  Y = abs(y);  col = col1;

			// Orthogonal trihedra
            if (n.cross(vec3(0,0,1)).norm() <= 1E-10) {
                e2 = vec3(1,0,0);
                e3 = vec3(0,1,0);
            }
            else {
                e2 = n.cross(vec3(0,0,1)).normalize();      // "Horizontal" direction on the rectangle plane. Unit vector
			    e3 = e2.cross(n).normalize(); 		        // "Vertical" direction on the rectangle plane. Unit vector
			
			    // Rotate to align with the orientation angle
			    e2 = e2.rotate(Omega*n).normalize();
			    e3 = e3.rotate(Omega*n).normalize();
            }
			

		}

        vec3 getPosition() {return position;}
		hit getHit(ray r) override;
        
		

};

hit rectangle::getHit(ray r) {

    ray r_rct = r.LorentzBoost(speed);
	
    vec3 rdir = r_rct.direction();
    
	double A = rdir.dot(n);
    double C = position.dot(n);

	if (A == 0) {
		return hit(false, vec4(), rdir);
	}

	double t = (C-r_rct.origin().spatials().dot(n))/A;

    if (t <= 0) {
		return hit(false, vec4(), rdir);
	}

	vec3 pos = r_rct.at(t/c);

    double Pu = (pos-position).dot(e2);
    double Pv = (pos-position).dot(e3);

     // Now checks if Pp is in (∓X/2, ∓Y/2, 0). 
    if (abs(Pu) > X/2 or abs(Pv) > Y/2) { 
        return hit(false, vec4(), rdir);
    }

    
    double coeff1 = 1.0;
	//TEMPORARY
	if (cos(2*pi*4/X*Pu)*sin(2*pi*4/X*Pv) > 0) {

		coeff1 = 0.66;

	}

	double coeff2 = sqrt((A*A+0.1)/1.1);

    color hit_color = coeff1*coeff2*col;

    return hit(true, vec4(pos.x(), pos.y(), pos.z(), t/c+r_rct.origin().ptime()).Lorentz(-speed), rdir, hit_color);
    
	
}

#endif // End of ifndef
