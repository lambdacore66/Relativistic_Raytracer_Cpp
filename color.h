#ifndef COLOR_H        // Checks if the header 'COLOR_H' is already defined
#define COLOR_H        // if not, defines it.

#include <iostream>

// Loads vec3 class definition
#include "vec3.h"

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Color has a specific utility that prints formated pixel color

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	
	// Divede the color by the number of samples so you can add the together to get the mean across samples
	// Include gamma correction with gamma = 2
	auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);                            // For MSAA 
    b = sqrt(scale * b);
	
	// Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
