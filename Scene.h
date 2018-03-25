#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "PointLight.h"
#include "Material.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sstream>
#include <chrono>
#include <GL/glew.h>
#include <GL/gl.h>   // The GL Header File
#include <GL/freeglut.h> // The GL Utility Toolkit (Glut) Header

using namespace std;

class Scene {


public:


    vector<Triplet> global_triplets;
    vector<Camera> _cameras;
    vector<Vertex> _vertices;
    vector<Mesh>   _meshes;

    vector<PointLight> _lights;
    vector<Material> _materials;


    vector<Vector3> _translations;
    vector<Vector3> _scalings;
    vector<Rotation> _rotations;

    vector< pair<char,int> > _operations;

    Color _background;
    Color _ambient;

    Scene(){}
    ~Scene(){}

    const std::vector<Camera>& Cameras() const {
        return _cameras;
    }

    void sceneData();

    void cameraTransformation(int camera_index);
    void projectionTransformation(int camera_index);
    void viewportTransformation(int camera_index);
    void cull(int camera_index);
    void rasterize(int camera_index, Image& img);
    void drawLine(Vertex a, Vertex b, Image& img);


    //////////////////////////////
    // READ SCENE FUNCTIONS HERE !
    //////////////////////////////
};

extern Scene* CurrentScene;
void ReadScene(int argc, char** argv);


#endif //RAYTRACER_SCENE_H
