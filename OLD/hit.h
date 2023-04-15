// Hit class definition
#ifndef HIT_H        // Checks if the header 'HIT_H' is already defined
#define HIT_H        // if not, defines it.


#include <cmath>
#include <iostream>

#include "vec4.h"


class hit {
	
	public:
				
		// Parametrized constructor. Orientation is the camera plane angle from the vertical up position.
		bool hitbool; vec4 where;
	
		hit(bool hit_= false, vec4 pos = vec4()) { 
			
			hitbool = hit_;
			where = pos; 

		}
		
		bool getBool() {return hitbool; }
		vec4 getWhere() {return where;}
		
};

#endif // End of ifndef
