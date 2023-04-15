// 3-vector class definition
#ifndef VEC3_H        // Checks if the header 'VEC3_H' is already defined
#define VEC3_H        // if not, defines it.


#include <cmath>
#include <iostream>

class vec3 {
	
	public:
		double vx; double vy; double vz;
		
		// Default constructor. Defines it at origin. Needs fixing
		// vec3() { vx = 0; vy = 0; vz = 0;}
		
		// Parametrized constructor.
		vec3(double ux = 0, double uy = 0, double uz = 0) {vx = ux; vy = uy; vz = uz;}
		
		
		//-----------------------------------------------------------------------------------------------------
		
		// Class method example. Here functions are defined 'inline' by default
		// void print_vec() { std::cout << "v = (" << x << ", " << y << ", " << z <<")";}
		
		// Components return methods
		double x() { return vx; }
		double y() { return vy; }
		double z() { return vz; }
		
		
		// Using Operator Overloading
		// Define the sum of two vec3
		vec3 operator+(vec3 u) { return vec3(vx+u.x(), vy+u.y(), vz+u.z()); }
		
		// Define the inverse sum of two vec3
		vec3 operator-() { return vec3(-vx, -vy, -vz); }
		
		// Define the substraction of two vec3
		vec3 operator-(vec3 u) { return vec3(vx-u.x(), vy-u.y(), vz-u.z()); }
		
		// Define the product by scalar. This way of doing overloading makes the 'this' pointer the first argument. 
		// This means that it always NEEDs a vec3 as it first argument and real*vec3 won't work. I need to define the other order
		// outside the class to make it work. See it below.
		vec3 operator*(double u) { return vec3(vx*u, vy*u, vz*u); }
		
		// This can also be performed by adding a friend overload operator:
		
		// Define the division by scalar
		vec3 operator/(double u) { return vec3(vx/u, vy/u, vz/u); }

				
		void print();
		double dot(vec3 u);
		vec3 cross(vec3 u);
		double norm2();
		double norm();
		vec3 normalize();
		vec3 rotate (vec3 w);
	
};

using color = vec3;   // RGB color

// Overloading helper. Allow reverse order.
const vec3 operator*( const double n, vec3 v )
{
    //no need to re-implement, since I already have vec3 * double defined
    return v * n;
}

// Class methods can be written like above or like this

// Print vector as a row
void vec3::print() {
	
	std::cout << "(" << vx << ", " << vy << ", " << vz <<")";	
	
}

// Scalar product
double vec3::dot(vec3 u) { return vx*u.x() + vy*u.y() + vz*u.z(); }

// Cross product
vec3 vec3::cross(vec3 u) { return vec3(vy*u.z() - vz*u.y(), vz*u.x() - vx*u.z(), vx*u.y() - vy*u.x()); }

// Norm^2. MAYBE TRY USING "THIS" POINTER
double vec3::norm2() { return vec3(vx, vy, vz).dot(vec3(vx, vy, vz)); }

// Norm
double vec3::norm() { return sqrt(vec3(vx, vy, vz).norm2()); }

// Get normalized vector
vec3 vec3::normalize() {return vec3(vx, vy, vz)/vec3(vx, vy, vz).norm(); }

vec3 vec3::rotate( vec3 u ) {
	
	double a = u.norm();      // Angle of rotation on radians
	
	if (a == 0) {
		
		return vec3(vx, vy, vz); 
		
	} else {
		
		vec3 n = u.normalize();   // Axis of rotation.
		
		double ca = cos(a);
		double sa = sin(a);
	
		// Matrix Rotation application
		double v1 =       (ca + n.x()*n.x()*(1-ca))*vx + (n.x()*n.y()*(1-ca) -n.z()*sa)*vy + (n.x()*n.z()*(1-ca) +n.y()*sa)*vz;
	
		double v2 = (n.x()*n.y()*(1-ca) + n.z()*sa)*vx +      (ca + n.y()*n.y()*(1-ca))*vy + (n.y()*n.z()*(1-ca) -n.x()*sa)*vz;
	
		double v3 = (n.x()*n.z()*(1-ca) - n.y()*sa)*vx + (n.y()*n.z()*(1-ca) +n.x()*sa)*vy +      (ca + n.z()*n.z()*(1-ca))*vz;
	
		return vec3(v1, v2, v3);
		
	}
	
}




#endif // End of ifndef






