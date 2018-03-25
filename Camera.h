#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <iostream>
#include "Vertex.h"
#include "Image.h"


using namespace std;

class Camera {


public:

      struct {
        Vector3 Forward, Up, Right;
    } _space;

    struct {
        float Left, Right, Bottom, Top;
        float Near, Far;

        int Width;
        int Height;

    } _imagePlane;

    Vector3 _position;


    Camera(Vector3 pos, Vector3 gaze, Vector3 _up, float _left, float _right, float _bottom, float _top, float _near, float _far, int _horres, int _verres)
    {
        _position = pos;
        _space.Forward = gaze;
        _space.Up = _up;
        _imagePlane.Left = _left;
        _imagePlane.Right = _right;
        _imagePlane.Bottom = _bottom;
        _imagePlane.Top = _top;
        _imagePlane.Near = _near;
        _imagePlane.Far = _far;
        _imagePlane.Width = _horres;
        _imagePlane.Height = _verres;
    }

    /*
     * BEWARE! You should render each camera by using this function, we will grade it according to regulations!
     */

    friend ostream& operator<<(ostream& os, Camera& mycam)
    {
        os << "## Camera Info ##" << endl;
        os << "Position: " << mycam._position << endl;
        os << "Forward: " << mycam._space.Forward << endl;
        os << "Up: " << mycam._space.Up << endl;
        os << "Right: " << mycam._space.Right << endl;
        os << "Left-Right-Bottom-Top-Distance: " << mycam._imagePlane.Left
                                          << " " << mycam._imagePlane.Right
                                          << " " << mycam._imagePlane.Bottom
                                          << " " << mycam._imagePlane.Top
                                          << " " << mycam._imagePlane.Near
                                          << " " << mycam._imagePlane.Far
                                          << endl;
        os << "Width-Height: " << mycam._imagePlane.Width << " " << mycam._imagePlane.Height << endl;
        return os;
    }

    Image Render() const;


};
    // inline Color computeColor(RayHitInfo& hitinfo, Vector3 v);
    // inline Color rayTrace(Ray& cameraray, int refl_count);

#endif //RAYTRACER_CAMERA_H
