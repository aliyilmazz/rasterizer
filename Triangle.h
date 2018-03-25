#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include <climits>
#include "Vertex.h"

class Triangle
{
public:
    Vertex _a, _b, _c;
    // This function gets a ray, and if the triangle intersects with the ray, returns true and fills the hitInfo struct
    // Else return false and leave hitInfo unchanged
    Triangle() {}
    Triangle(Vertex __a,Vertex __b,Vertex __c): _a(__a), _b(__b), _c(__c) {}
    Vertex a() {return _a;}
    Vertex b() {return _b;}
    Vertex c() {return _c;}

    friend std::ostream& operator<<(std::ostream& os, Triangle& tri)
    {
        os << "a: " << tri.a()._position << " b: " << tri.b()._position << " c: " << tri.c()._position;
        // os << "a_color: " << tri._a._color << " b_color: " << tri._b._color << " c_color: " << tri._c._color << "\n";
        return os;
    }
    float f_01(int x, int y)
    {
        int x0 = _a._position._data[0];
        int y0 = _a._position._data[1];
        int x1 = _b._position._data[0];
        int y1 = _b._position._data[1];
        return x*(y0-y1) + y*(x1-x0) + x0*y1 - y0*x1;
    }
    float f_12(int x, int y)
    {
        int x1 = _b._position._data[0];
        int y1 = _b._position._data[1];
        int x2 = _c._position._data[0];
        int y2 = _c._position._data[1];
        return x*(y1-y2) + y*(x2-x1) + x1*y2 - y1*x2;
    }
    float f_20(int x, int y)
    {
        int x0 = _a._position._data[0];
        int y0 = _a._position._data[1];
        int x2 = _c._position._data[0];
        int y2 = _c._position._data[1];
        return x*(y2-y0) + y*(x0-x2) + x2*y0 - y2*x0;
    }
};

#endif //RAYTRACER_TRIANGLE_H
