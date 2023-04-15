#ifndef HITTABLE_H        // Checks if the header 'HITTABLE_H' is already defined
#define HITTABLE_H        // if not, defines it.

#include <cmath>
#include <iostream>
#include <vector>

#include "ray.h"
#include "hit.h"

class hittable {
	public:
		virtual hit getHit(ray r) = 0;
		// virtual means that the function is defined in derived classes, ie, spheres class, planes class, ... 
};

#endif