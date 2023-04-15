#include <iostream>
#include <fstream>

constexpr double c = 1;

#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "cam.h"
#include "hit.h"

#include "sphere.h"
#include "plane.h"



int main() {
	
	// Camera definition
	
	vec4 pos(0,0,0,0);
	vec3 dir(1,0,0);
	double omega = 0.0;
	double fov = 90;
	double aspect_ratio = 16.0/9;
	int height = 900;
	int width = floor(height*aspect_ratio);
	
	cam cam1(pos, dir, omega, fov, height, aspect_ratio);
	
	//cam1.get_u().print();
	//cam1.get_v().print();
	//cam1.get_w().print();
	
	
	sphere sph(vec4(15, -3, 0, 0), vec3(), 2, color(1, 0, 0));
	
	std::fstream image;
	image.open("image.ppm", std::ios::out);
	
	image << "P3\n" << width << ' ' << height << "\n255\n"; 
	
	for (int j = height; j >= 1 ; j--) {
		for (int i = 1; i <= width; i++) {
			
			ray ray1 = cam1.get_ray(i,j);
			hit rayhit = sph.getHit(ray1);
			
			if (rayhit.getBool()) {
				write_color(image, sph.getColor(ray1, rayhit), 1);
			}
			else {
				image << 0 << ' ' << 0 << ' ' << 0 << '\n';
			}
			
		}
		
	}	
	
	image.close();

	return 0;

}
