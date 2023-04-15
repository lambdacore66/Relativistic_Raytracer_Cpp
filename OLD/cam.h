// Camera class definition
#ifndef CAM_H        // Checks if the header 'CAM_H' is already defined
#define CAM_H        // if not, defines it.


#include <cmath>
#include <iostream>
#include "vec3.h"
#include "vec4.h"
#include "ray.h"

const double pi = 3.1415926535897932385;

class cam {
	
	public:
				
		// Parametrized constructor. Orientation is the camera plane angle from the vertical up position.
		vec4 position; vec3 focal_vector; double orientation = 0; double fov; int pixels_ver; double aspect_ratio; vec3 w,v,u;
	
		cam(vec4 pos = vec4(), vec3 f_v = vec3(1,0,0), double ornttn = 0, double fov_a = 90, int size = 720,  double asprt = 1) { 
		
			position = pos; focal_vector = f_v; orientation = ornttn; fov = fov_a; pixels_ver = size; aspect_ratio = asprt;
			
			// Orthogonal trihedra
			w = focal_vector.normalize();              // Direction of view point. Unit vector
			u = w.cross(vec3(0,0,1)).normalize();      // "Horizontal" direction on the camera plane. Unit vector
			v = u.cross(w).normalize(); 		       // "Vertical" direction on the camera plane. Unit vector
			
			// Rotate to align with the orientation angle
			u = u.rotate(orientation*w);
			v = v.rotate(orientation*w);

		}
		

		
		//-----------------------------------------------------------------------------------------------------
		
		// Class method example. Here functions are defined 'inline' by default
		// void print_vec() { std::cout << "v = (" << x << ", " << y << ", " << z <<")";}
		
		// Components return methods
		vec4 get_pos() { return position; } 
		vec3 get_f_vector() { return focal_vector; } 
		double get_orientation() { return orientation; }
		double get_fov() { return fov;}
		void print_imagesize() { std::cout << pixels_ver*aspect_ratio << "x" << pixels_ver; }
		double get_aspect_ratio() { return aspect_ratio; }
		
		
		
		
		vec3 get_w() { return w; }
		vec3 get_v() { return v; } 
		vec3 get_u() { return u; } 
		
		
		ray get_ray(int i, int j);
		
//	public:
//		vec4 position; vec3 focal_vector; double orientation = 0; double fov; double aspect_ratio;
		
	
};

// Get_ray returns the ray corresponding to the i,j pixel

ray cam::get_ray(int i, int j) {
	
	double Lx = 2*focal_vector.norm()*tan(fov*pi/360); double Ly = Lx/aspect_ratio;
	
	double delta_u = Lx/2/pixels_ver/aspect_ratio; 
	double delta_v = Ly/2/pixels_ver;
	
	vec3 ray_dir = focal_vector + (i-pixels_ver*aspect_ratio/2)*delta_u*u + (j-pixels_ver/2)*delta_v*v;
	return ray(position.spatials(), ray_dir.normalize());
	
}


#endif // End of ifndef
