// Angles class definition
#ifndef ANGLE_H        // Checks if the header 'ANGLE_H' is already defined
#define ANGLE_H        // if not, defines it.


#include <cmath>
#include <iostream>


const double pi = 3.1415926535897932385;

class angle {
	
	public:
		double alpha;
		
		angle(double beta = 0) { alpha = beta- 2*pi*floor(beta/(2*pi));} // beta = alpha mod 2pi  
		
		// Return angle as double
		double getValue() { return alpha; }
		
		// Define the sum of two angles
		angle operator+(angle beta) { return angle(alpha + beta.getValue() ); }
		
		// Define the inverse of an angle
		angle operator-() { return angle(2*pi - alpha ); }
		
		// Define the substraction of two angles
		angle operator-(angle beta) { return angle(alpha - beta.getValue() ); }
		
		// Define the product by scalar.
		angle operator*(double u) { return angle(u*alpha); }
		
		
		// Define the division by scalar
		angle operator/(double u) { return angle(alpha/u); }
		
		
		
		void print();
		
	
	
};

// Reverse order for product by a scalar
const angle operator*( const double u, angle alpha )
{
    return alpha * u;
}

// Print vector as a row
void angle::print() {
	
	std::cout << alpha;	
	
}


#endif // End of ifndef
