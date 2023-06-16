#ifndef CUBE_H        // Checks if the header 'CUBE_H' is already defined
#define CUBE_H        // if not, defines it.


#include <cmath>
#include <iostream>
#include <vector>
#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "hit.h"
#include "plane.h"
#include "rectangle.h"
#include "hittable.h"

class cube : public hittable {
	
	public:

		// cubes are defined as:
		vec3 position; vec3 speed; double theta; double phi; double X; double Y; double Z; color col;
		std::vector<rectangle> cube_faces;

		cube(
			vec3 pos = vec3(0,0,0), vec3 v = vec3(0,0,0), double theta1 = 0.0, double phi1 = 0.0, 
			double x = 0.0, double y = 0.0, double z = 0.0, color col1 = color(1,1,1)			 ) { 

			
			position = pos;
			speed = v;
			theta = theta1;
			phi = phi1;
			X = x;
			Y = y;
			Z = z;
			col = col1;
		
			// Add the 6 XYZ aligned faces
			cube_faces.push_back(rectangle(vec3(-X/2,0,0)+position, vec3(1,0,0), Y, Z, 0.0, 0.0, speed, col));
			cube_faces.push_back(rectangle(vec3(0,-Y/2,0)+position, vec3(0,1,0), X, Z, 0.0, 0.0, speed, col));
			cube_faces.push_back(rectangle(vec3(0,0,-Z/2)+position, vec3(0,0,1), X, Y, 0.0, 0.0, speed, col));

			cube_faces.push_back(rectangle(vec3(X/2,0,0)+position, vec3(1,0,0), Y, Z, 0.0, 0.0, speed, col));
			cube_faces.push_back(rectangle(vec3(0,Y/2,0)+position, vec3(0,1,0), X, Z, 0.0, 0.0, speed, col));
			cube_faces.push_back(rectangle(vec3(0,0,Z/2)+position, vec3(0,0,1), X, Y, 0.0, 0.0, speed, col));

		}
		
		hit getHit(ray r) override;

};


hit cube::getHit(ray r) {

	double temp = std::numeric_limits<double>::max(); 
	hit real_hit(false);

	// Check the other faces
	for (int k = 0; k < 6; k++) {

		rectangle face = cube_faces.at(k);
		hit face_hit = face.getHit(r);

		if (face_hit.getBool() and  -face_hit.getWhere().ptime() < temp) { // As time is "played" backwards, you need to reverse the time coordinate.
																	       // You could also take into account the start time and camera initial time, but
																	       // it is not necessary.
			temp = -face_hit.getWhere().ptime();
			real_hit = face_hit;

		}

	}

	return real_hit;

}
#endif // End of ifndef
