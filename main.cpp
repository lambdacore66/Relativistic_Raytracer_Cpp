#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

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

	vec4 pos(0, 0, 1, 0);
	vec3 focal(1, 0, 0);
	double omega = 0.0;
	double fov = 120;
	double aspect_ratio = 7.0/3;
	int height = 360;
	int width = floor(height*aspect_ratio);

	const auto bytesPerPixel = 3;
	unsigned char* image = new unsigned char[width * height * bytesPerPixel];
	std::fill(image, image + width * height * bytesPerPixel, 0);
	const auto quality    = 95;

	cam cam1(pos, focal, omega, fov, height, aspect_ratio);

	std::vector<std::unique_ptr<hittable>> obj_list;

	//Add rectangles
									        //Position       Normal     X    Y      Rpos      Omega1 Omega2        v             Color
	//obj_list.emplace_back(new rectangle(vec3(1.5, -4, 0), vec3(1,0,0), 2.0, 3.0, vec3(1,0,0), pi/4, -pi/4, 0.95*c*vec3(-1,0,0), color(1,1,0)));
	//obj_list.emplace_back(new rectangle(vec3(3, -3, 0), vec3(0,1,0), 3.0, 3.0, vec3(1,0,0), pi/4, -pi/4, 0.95*c*vec3(-1,0,0), color(1,1,0)));


	//Add cubes
									//Position            v            Phi Theta  X    Y    Z       Color
	obj_list.emplace_back(new cube(vec3(3, 4, 0), 0.95*c*vec3(-1,0,0), pi/4, -pi/4, 3.0, 2.0, 3.0, color(1,0,0)));
	obj_list.emplace_back(new cube(vec3(3,-4, 0), 0.95*c*vec3(-1,0,0), 0.0, 0.0, 3.0, 2.0, 3.0, color(1,1,0)));

	//Add planes
									//Normal     C      Rpos     Omega1 Omega2     v            Color
	obj_list.emplace_back(new plane(vec3(0,0,1), 0, vec3(5,0,0),  0.0,  0.0, vec3(0,0,0), color(1,1,1)));
	
	//obj_list.emplace_back(new plane(vec3(0,0,1), 0, vec3(5,0,0),  pi/4, -pi/4, 0.95*c*vec3(-1,0,0), color(1,0,0)));      // Same planes with and without rotations involved
	//obj_list.emplace_back(new plane(vec3(-1, 1, sqrt(2)), -5/2, vec3(5,0,0),  0.0, 0.0,  0.95*c*vec3(-1,0,0), color(1,0,0)));


	//Add spheres
									//Position    R  Omega1 Omega2        v                Color
	//obj_list.emplace_back(new sphere(vec3(8,0,0), 3, pi/4, -pi/4,  0.8*c*vec3(-1,0,0), color(1,0,0)));

	double fps = 10;
	double t0 = -1.0;
	double tf = t0+4;

	double t = t0;
	int frame = 0;

	int numberFormat = 1;
	int Nframes = int(floor(abs(tf-t0)*fps));

	if (Nframes != 0) {
		numberFormat = int(log10(Nframes) + 1);
	}
	
	while(t <= tf) {  //NEEDS TIME RATE IMPLEMENTATION

		const auto start = high_resolution_clock::now();

		for (int j = 0 ; j < height; j++) {

			#pragma omp parallel 
    		#pragma omp for 

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

		const auto end = high_resolution_clock::now();

		duration<double, std::milli> frametime_chrono = end - start;
		double frametime_sec = frametime_chrono.count()/1E3;

		std::string framenumber = std::to_string(frame);
		std::string s = "./frames/frame"+framenumber.insert(0, numberFormat - std::min(std::string::size_type(numberFormat), framenumber.length()), '0')+".png";
		char const *name = s.c_str();

		stbi_write_png(name, width, height, bytesPerPixel, image, width*bytesPerPixel);

		std::fill(image, image + width * height * bytesPerPixel, 0);


		double time_remaining = (Nframes-frame)*frametime_sec;
		int mins_remaining = int(floor(time_remaining / 60));
		int secs_remaining = int(time_remaining-60*floor(time_remaining / 60));

		std::cout << int(100*frame/Nframes) << "% - Time Remaining: ";
		std::cout << mins_remaining <<" m " << secs_remaining << " s \r";

		frame++;
		t = t + 1/fps;

	}

	//ffmpeg -framerate 10 -i ./frames/frame%02d.png -vcodec libx264 -pix_fmt yuv420p -b:v 5000k output.mp4
	std::string scmd = "ffmpeg -framerate "+std::to_string(int(fps))+" -i ./frames/frame%0"+std::to_string(numberFormat)+"d.png -vcodec libx264 -pix_fmt yuv420p -b:v 5000k output.mp4";
	char const *cmd = scmd.c_str();

	system(cmd);

	std::cout << "Render finished";

	return 0;

}
