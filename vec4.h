// 4-vector class definition
#ifndef VEC4_H        // Checks if the header 'VEC3_H' is already defined
#define VEC4_H        // if not, defines it.


#include <cmath>
#include <iostream>

#include "vec3.h"

class vec4 {
	
	public:
		double vx; double vy; double vz; double vt;
		
		// Default constructor. Defines it at origin. Needs fixing
		// vec3() { vx = 0; vy = 0; vz = 0;}
		
		// Parametrized constructor.
		vec4(double ux = 0, double uy = 0, double uz = 0, double ut = 0) { vx = ux; vy = uy; vz = uz; vt = ut;}
		
		
		//-----------------------------------------------------------------------------------------------------
		
		// Class method example. Here functions are defined 'inline' by default
		// void print_vec() { std::cout << "v = (" << x << ", " << y << ", " << z <<")";}
		
		// Components return methods
		double x() { return vx; }
		double y() { return vy; }
		double z() { return vz; }
		double t() { return vt; }
		
		
		// Using Operator Overloading
		// Define the sum of two vec3
		vec4 operator+(vec4 u) { return vec4(vx+u.x(), vy+u.y(), vz+u.z(), vt+u.t()); }
		
		// Define the inverse sum of two vec4
		vec4 operator-() { return vec4(-vx, -vy, -vz, -vt); }
		
		// Define the substraction of two vec4
		vec4 operator-(vec4 u) { return vec4(vx-u.x(), vy-u.y(), vz-u.z(), vt-u.t()); }
		
		// Define the product by scalar. This way of doing overloading makes the 'this' pointer the first argument. 
		// This means that it always NEEDs a vec3 as it first argument and real*vec3 won't work. I need to define the other order
		// outside the class to make it work. See it below.
		vec4 operator*(double u) { return vec4(vx*u, vy*u, vz*u, vt*u); }
		
		// This can also be performed by adding a friend overload operator:
		
		// Define the division by scalar
		vec4 operator/(double u) { return vec4(vx/u, vy/u, vz/u, vt/u); }

				
		void print();
		vec4 dual();
		double sprod(vec4 u);
		double norm2();
		double norm();
		vec3 spatials();
		double ptime();
		vec4 Galileo(vec3 v);
		vec4 Lorentz(vec3 v);
	
};

// Overloading helper. Allow reverse order.
const vec4 operator*( const double n, vec4 v )
{
    //no need to re-implement, since I already have vec3 * double defined
    return v * n;
}

// Class methods can be written like above or like this

// Print vector as a row
void vec4::print() {
	
	std::cout << "(" << vx << ", " << vy << ", " << vz << ", " << vt <<")";	
	
}

// Computes the dual to the 4-vector/form
vec4 vec4::dual() { return vec4(vx, vy, vz, -vt); }

// Minkowski scalar product
double vec4::sprod(vec4 u) { return vx*u.x() + vy*u.y() + vz*u.z() - vt+u.t(); }

// Norm^2. MAYBE TRY USING "THIS" POINTER
double vec4::norm2() { return vec4(vx, vy, vz, vt).sprod(vec4(vx, vy, vz, vt)); }

// Norm
double vec4::norm() { return sqrt(vec4(vx, vy, vz, -vt).norm2()); }

// Extract spatial coordinates
vec3 vec4::spatials() { return vec3(vx, vy, vz);}

// Extract time coordinate
double vec4::ptime() { return vt;}

vec4 vec4::Galileo(vec3 v) {

	if (v.norm() >= c) {
		std::cerr << "error: Object cannot be as fast or faster than light.\n";
    	std::exit;
	} 

	vec3 r = vec3(vx, vy, vz)-vt*v;
	return vec4(r.x(), r.y(), r.z(), vt);
	
}

vec4 vec4::Lorentz(vec3 v) {

	double norm = v.norm();

	if (norm <= 1E-10) {
		return *this;
	}
	else if (norm >= c) {
		std::cerr << "error: Object cannot be as fast or faster than light.\n";
    	std::exit;
	}

	vec3 n = v/norm;

	double b = norm/c;
	double g = 1/sqrt(1-b*b);

	vec3 r = vec3(vx, vy, vz)+(g-1)*vec3(vx, vy, vz).dot(n)*n-g*vt*v;
	double t = g*(vt-b*vec3(vx, vy, vz).dot(n)/c);

	return vec4(r.x(), r.y(), r.z(), t);
	
}


#endif // End of ifndef
