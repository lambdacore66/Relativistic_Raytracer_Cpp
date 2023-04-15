// Hit class definition
#ifndef HIT_H        // Checks if the header 'HIT_H' is already defined
#define HIT_H        // if not, defines it.


#include <cmath>
#include <iostream>

#include "vec3.h"
#include "vec4.h"
#include "color.h"


class hit {
	
	public:
				
		// Parametrized constructor. Orientation is the camera plane angle from the vertical up position.
		bool hitbool; vec4 where; vec3 hit_dir; color col;
	
		hit(bool hit_= false, vec4 pos = vec4(), vec3 hit_direction = vec3(), color col1 = vec3(0,0,0)) { 
			
			hitbool = hit_;
			where = pos; 
			hit_dir = hit_direction;
			col = col1;

		}
		
		bool getBool() {return hitbool; }
		vec4 getWhere() {return where;}
		vec3 getHit_direction() {return hit_dir; }
		vec3 getColor() {return col; }
		
};

#endif // End of ifndef
