#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"

using namespace std;

class Scene;

class Material {


public:
	Color ambient;
    Color diffuse;
    Color specular;
    float specexp;

	Material(Color _ambient, Color _diffuse, Color _specular, float _specexp): ambient(_ambient), diffuse(_diffuse), specular(_specular), specexp(_specexp) {}

  /*  Color ambient() { return ambient; }
    Color diffuse() { return diffuse; }
    Color specular() { return specular; }
    Color reflectance() { return reflectance; } */


     /*
      * Implement a Calculate function that does Diffuse, Specular and Ambient, Reflective shading
      * Answer: The Corresponding calculations are implemented in my computeColor() function's main body, at camera.cpp.
      */

    friend std::ostream& operator<<(std::ostream& os, Material& mat)
    {
    	os << mat.ambient << " - " << mat.diffuse << " - " << mat.specular << " - " << mat.specexp;
    	return os;
    }
};


#endif //RAYTRACER_MATERIAL_H
