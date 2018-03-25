#ifndef RAYTRACER_VERTEX_H
#define RAYTRACER_VERTEX_H

#include "Vector3.h"
#include "Color.h"
#include <vector>

using namespace std;

class Vertex {

public:

    Vector3 _position;
    Vector3 _normal;
    Color _color;
    int rotated;
    float _normalcount;
    vector< pair<int,int> > triangle_ids;
    vector<Vector3> normals;
    int meshnumber;

    Vertex()
    {
        _position = Vector3(0,0,0);
        _color = Color(0,0,0);
        _normal = Vector3(0,0,0);
        rotated = 0;
        _normalcount = 0;
        triangle_ids.clear();
        normals.clear();
        meshnumber=0;
    }

    Vertex(Vector3 position, Color color)
    {
        _position = position;
        _color = color;
    }

    friend std::istream &operator>>(std::istream &stream, Vertex &vertex)
    {
        stream >> vertex._position >> vertex._color;
        return stream;
    }

    friend std::ostream& operator<<(std::ostream& os, Vertex& vertex)
    {
        os << vertex._position;
        return os;
    }
};

#endif //RAYTRACER_VERTEX_H
