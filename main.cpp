#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

constexpr double c = 5;

#include "vec3.h"
#include "color.h"
#include "vec4.h"
#include "ray.h"
#include "cam.h"
#include "hit.h"
#include "hittable.h"

#include "sphere.h"
#include "plane.h"
#include "rectangle.h"
#include "cube.h"

int main() {

	// Camera definition

	vec4 pos(0, 0, 0, 0);
	vec3 dir(1, 0, 0);
	double omega = 0.0;
	double fov = 120;
	double aspect_ratio = 7.0/3;
	int height = 360;
	int width = floor(height*aspect_ratio);

	const auto bytesPerPixel = 3;
	unsigned char* image = new unsigned char[width * height * bytesPerPixel];
	std::fill(image, image + width * height * bytesPerPixel, 0);
	const auto quality    = 95;

	cam cam1(pos, dir, omega, fov, height, aspect_ratio);

	std::vector<std::unique_ptr<hittable>> obj_list;

	obj_list.emplace_back(new rectangle(vec3(1.5, -4, 0), 0.95*c*vec3(-1,0,0), vec3(1,0,0), 0.0, 2.0, 3.0, color(1,1,0)));
	obj_list.emplace_back(new rectangle(vec3(3, -3, 0), 0.95*c*vec3(-1,0,0), vec3(0,1,0), 0.0, 3.0, 3.0, color(1,1,0)));

	obj_list.emplace_back(new cube(vec3(3, 4, 0), 0.95*c*vec3(-1,0,0), 0.0, 0.0, 3.0, 2.0, 3.0, color(1,0,0)));  //ROTATIONS ARE BROKEN RIGHT NOW. MUST BE FIXED IN RAY CLASS

	obj_list.emplace_back(new rectangle(vec3(0,0,-0.5), vec3(0,0,0), vec3(0,0,1), 0.0, 100.0, 100.0, color(1,1,1)));

	//obj_list.emplace_back(new sphere(vec3(8,-6,1), 0.95*c*vec3(0,-1,0), 1.2, color(1,0,0)));

	double fps = 60;
	double t0 = -7;
	double tf = t0+10;

	double t = t0;
	int frame = 0;

	int numberFormat = int(log10(floor(abs(tf-t0)*fps)) + 1);
	
	while(t <= tf) {  //IMPLEMENT TIME RATE

		for (int j = 0 ; j < height; j++) {
			for (int i = 0; i < width; i++) {

				auto offset = ((height-1-j) * width + i) * bytesPerPixel;

				ray ray1 = cam1.get_ray(i, j, t);

				double temp = std::numeric_limits<double>::max();

				for (int k = 0; k < obj_list.size(); k++) {

					hittable* obj = obj_list.at(k).get();
					hit rayhit = obj->getHit(ray1);

				 	if (rayhit.getBool() and  -rayhit.getWhere().ptime() < temp) { // As time is "played" backwards, you need to reverse the time coordinate.
																				   // You could also take into account the start time and camera initial time, but
																				   // it is not necessary.
						temp = -rayhit.getWhere().ptime();

						color col = rayhit.getColor();

						image[offset  ] = int(255*col.x());
						image[offset+1] = int(255*col.y());
						image[offset+2] = int(255*col.z());

					}

				}
			}
		}

		// FIXEAR CUANDO SOLO HAYA UN FRAME. DA STD::LENGTH_ERROR

		std::string framenumber = std::to_string(frame);
		std::string s = ".\\frames\\frame"+framenumber.insert(0, numberFormat - std::min(std::string::size_type(numberFormat), framenumber.length()), '0')+".png";
		char const *name = s.c_str();

		stbi_write_png(name, width, height, bytesPerPixel, image, width*bytesPerPixel);

		std::fill(image, image + width * height * bytesPerPixel, 0);

		std::cout << int(100*frame/(abs(tf-t0)*fps))<< "% - Time Remaining: " << "NOT YET IMPLEMENTED" <<"\r";

		frame++;
		t = t + 1/fps;

	}

	std::string scmd = "python render.py "+std::to_string(int(fps));
	char const *cmd = scmd.c_str();

	system(cmd);

	std::cout << "Render finished";

	return 0;

}
