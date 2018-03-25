#include "Scene.h"
#include <iostream>
#include <cstring>

using namespace std;


GLuint vertexAttribBuffer;
GLuint indexBuffer;

// GLuint vboIndex;
// GLuint indexbuf;

GLfloat* vertexData;
GLfloat* normalData;
GLuint* indexData;

int totalNumTriangles;
int totalNumVertices;

int vertexPosDataSizeInBytes;


int determineOffset(int mesh_index)
{
    int i=0;
    while (i<CurrentScene->global_triplets.size())
    {
        if(CurrentScene->global_triplets[i].meshindex==mesh_index)
            return i;
        i++;
    }
    return -1;
}

void setLights() // light0,1 conf
{
    int lightCount = CurrentScene->_lights.size();

    float ambx = CurrentScene->_ambient._channels[0];
    float amby = CurrentScene->_ambient._channels[1];
    float ambz = CurrentScene->_ambient._channels[2];
    float global_amb[] = {ambx, amby, ambz, 1.0};
    for(int i=0; i<lightCount; i++)
    {
        // cout << "light0 conf done." << endl;
        float posx = CurrentScene->_lights[i].light_position._data[0];
        float posy = CurrentScene->_lights[i].light_position._data[1];
        float posz = CurrentScene->_lights[i].light_position._data[2];
        float difx = CurrentScene->_lights[i].light_intensity._channels[0];
        float dify = CurrentScene->_lights[i].light_intensity._channels[1];
        float difz = CurrentScene->_lights[i].light_intensity._channels[2];
        float light_pos[] = {posx, posy, posz, 1.0};
        float light_dif[] = {difx, dify, difz, 1};
        glEnable(GL_LIGHT0+i);
        glLightfv(GL_LIGHT0+i, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0+i, GL_DIFFUSE, light_dif);
        glLightfv(GL_LIGHT0+i, GL_SPECULAR, light_dif);
        glLightfv(GL_LIGHT0+i, GL_AMBIENT, global_amb);
    }
}

void setBackground() // background conf
{
    GLfloat r = CurrentScene->_background._channels[0];
    GLfloat g = CurrentScene->_background._channels[1];
    GLfloat b = CurrentScene->_background._channels[2];
    glClearColor(r,g,b,1.0); // works
}

void updateLightPositions()
{
    int lightCount = CurrentScene->_lights.size();

    for(int i=0; i<lightCount; i++)
    {
        // cout << "light0 conf done." << endl;
        float posx = CurrentScene->_lights[i].light_position._data[0];
        float posy = CurrentScene->_lights[i].light_position._data[1];
        float posz = CurrentScene->_lights[i].light_position._data[2];
        float light_pos[] = {posx, posy, posz, 1.0};
        glLightfv(GL_LIGHT0+i, GL_POSITION, light_pos);
    }
}

void init()
{

    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    totalNumVertices = CurrentScene->_vertices.size();
    totalNumTriangles = CurrentScene->global_triplets.size();

    vertexData = (GLfloat*)malloc(sizeof(GLfloat)*totalNumVertices*3);
    normalData = (GLfloat*)malloc(sizeof(GLfloat)*totalNumVertices*3);
    indexData = (GLuint*)malloc(sizeof(GLuint)*totalNumTriangles*3);

    for (int i=0; i<totalNumVertices; i++)
    {
        vertexData[3*i] = CurrentScene->_vertices[i]._position._data[0];
        vertexData[3*i+1] = CurrentScene->_vertices[i]._position._data[1];
        vertexData[3*i+2] = CurrentScene->_vertices[i]._position._data[2];

        normalData[3*i] = CurrentScene->_vertices[i]._normal._data[0];
        normalData[3*i+1] = CurrentScene->_vertices[i]._normal._data[1];
        normalData[3*i+2] = CurrentScene->_vertices[i]._normal._data[2];
    }

    for(int i=0; i<totalNumTriangles; i++)
    {
        indexData[3*i] = CurrentScene->global_triplets[i].one;
        indexData[3*i+1] = CurrentScene->global_triplets[i].two;
        indexData[3*i+2] = CurrentScene->global_triplets[i].three;
    }

    glGenBuffers(1, &vertexAttribBuffer); // buffer for both normals and positions.
    glGenBuffers(1, &indexBuffer);

    vertexPosDataSizeInBytes = totalNumVertices*3*sizeof(GLfloat);
    int vertexNorDataSizeInBytes = totalNumVertices*3*sizeof(GLfloat);
    int indexDataSizeInBytes = totalNumTriangles*3*sizeof(GLuint);

    glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer); // activate buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ARRAY_BUFFER, totalNumVertices * 6 * sizeof(GLfloat), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexPosDataSizeInBytes, vertexData);
    glBufferSubData(GL_ARRAY_BUFFER, vertexPosDataSizeInBytes, vertexNorDataSizeInBytes, normalData);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSizeInBytes, indexData, GL_STATIC_DRAW);

    setBackground();
    setLights();

    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // glEnable(GL_COLOR_MATERIAL);
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /* ---------- set camera ----------- */
    Vector3 posplusgaze = CurrentScene->_cameras[0]._position + CurrentScene->_cameras[0]._space.Forward;
    float camx, camy, camz;
    float upx, upy, upz;
    float ppgx = posplusgaze._data[0];
    float ppgy = posplusgaze._data[1];
    float ppgz = posplusgaze._data[2];
    camx = CurrentScene->_cameras[0]._position._data[0];
    camy = CurrentScene->_cameras[0]._position._data[1];
    camz = CurrentScene->_cameras[0]._position._data[2];
    upx = CurrentScene->_cameras[0]._space.Up._data[0];
    upy = CurrentScene->_cameras[0]._space.Up._data[1];
    upz = CurrentScene->_cameras[0]._space.Up._data[2];
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, ppgx, ppgy, ppgz, upx, upy, upz);
    /***************************************/

    // update light positions after camera.
    updateLightPositions();

    for(vector<Mesh>::iterator it_mesh = CurrentScene->_meshes.begin(); it_mesh!=CurrentScene->_meshes.end(); it_mesh++)
    {
        glPushMatrix();

        // int triangle_count = (*it_mesh).triplets.size();

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        int numberoftriangles = (*it_mesh).triplets.size();
        int offset = determineOffset((*it_mesh).model_id-1)*3*sizeof(GLuint);
        // cout << "offset for meshid: " << (*it_mesh).model_id-1 << " = " << offset << ", numoftriangles: " << numberoftriangles << endl;

        /*-------- Material Setup --------*/
        int mat_index = (*it_mesh).material_id-1;
        GLfloat ambx = CurrentScene->_materials[mat_index].ambient._channels[0];
        GLfloat amby = CurrentScene->_materials[mat_index].ambient._channels[1];
        GLfloat ambz = CurrentScene->_materials[mat_index].ambient._channels[2];

        GLfloat difx = CurrentScene->_materials[mat_index].diffuse._channels[0];
        GLfloat dify = CurrentScene->_materials[mat_index].diffuse._channels[1];
        GLfloat difz = CurrentScene->_materials[mat_index].diffuse._channels[2];

        GLfloat specx = CurrentScene->_materials[mat_index].specular._channels[0];
        GLfloat specy = CurrentScene->_materials[mat_index].specular._channels[1];
        GLfloat specz = CurrentScene->_materials[mat_index].specular._channels[2];
        // cout << "matindex: " << mat_index << endl;
        // cout << "ambient: " << ambx << " " << amby << " " << ambz << endl;
        // cout << "dif: " << difx << " " << dify << " " << difz << endl;
        // cout << "spec: " << specx << " " << specy << " " << specz << " " << CurrentScene->_materials[mat_index].specexp << endl;
        GLfloat ambColor[4] = {ambx, amby, ambz, 1.0};
        GLfloat difColor[4] = {difx, dify, difz, 1.0};
        GLfloat specColor[4] = {specx, specy, specz, 1.0};
        GLfloat specExp[1] = {CurrentScene->_materials[mat_index].specexp};

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specColor);
        glMaterialfv(GL_FRONT, GL_SHININESS, specExp);
        /*-------- Material Setup Ends --------*/

        if((*it_mesh).model_type==1)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if((*it_mesh).model_type==2)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }


        glVertexPointer(3, GL_FLOAT, 0, 0);
        glNormalPointer(GL_FLOAT, 0, (void*)vertexPosDataSizeInBytes);
        glDrawElements(GL_TRIANGLES, 3*numberoftriangles, GL_UNSIGNED_INT, (void*)offset);
        glPopMatrix();
    }
    glutSwapBuffers();
}


void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
    w = w < 1 ? 1 : w; // clamping the values below 1, to 1.
    h = h < 1 ? 1 : h; // for values above 1, it stays at it is.

    glViewport(0, 0, w, h); // viewport setup.

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(CurrentScene->_cameras[0]._imagePlane.Left,
              CurrentScene->_cameras[0]._imagePlane.Right,
              CurrentScene->_cameras[0]._imagePlane.Bottom,
              CurrentScene->_cameras[0]._imagePlane.Top,
              CurrentScene->_cameras[0]._imagePlane.Near,
              CurrentScene->_cameras[0]._imagePlane.Far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    Vector3 left = crossProduct(CurrentScene->_cameras[0]._space.Forward, CurrentScene->_cameras[0]._space.Up);
    switch(key)
    {
        case 'w':
            CurrentScene->_cameras[0]._position = CurrentScene->_cameras[0]._position + normalize(CurrentScene->_cameras[0]._space.Forward)*0.05;
            break;
        case 's':
            CurrentScene->_cameras[0]._position = CurrentScene->_cameras[0]._position - normalize(CurrentScene->_cameras[0]._space.Forward)*0.05;
            break;
        case 'a':
            CurrentScene->_cameras[0]._space.Forward = arbitrary_rotate(CurrentScene->_cameras[0]._space.Forward, 0.5, Vector3(0,1,0));
            break;
        case 'd':
            CurrentScene->_cameras[0]._space.Forward = arbitrary_rotate(CurrentScene->_cameras[0]._space.Forward, -0.5, Vector3(0,1,0));
            break;
        case 'u':
            CurrentScene->_cameras[0]._space.Forward = arbitrary_rotate(CurrentScene->_cameras[0]._space.Forward, 0.5, left);
            break;
        case 'j':
            CurrentScene->_cameras[0]._space.Forward = arbitrary_rotate(CurrentScene->_cameras[0]._space.Forward, -0.5, left);
            break;
        default:
            break;
    }
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Please provide scene and camera files" << std::endl;
        return 1;
    }

    ReadScene(argc,argv);
    // CurrentScene->sceneData();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(CurrentScene->_cameras[0]._imagePlane.Width, CurrentScene->_cameras[0]._imagePlane.Height);
    glutCreateWindow("Horse and Mug Scene");
    glewInit();

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    delete CurrentScene;
    return 0;
}


// hazir vertex ve normal datasi
    // vertexData[0] = 17.717;
    // vertexData[1] = 0.02;
    // vertexData[2] = 16.94;
    // vertexData[3] = -17.717;
    // vertexData[4] = 0.02;
    // vertexData[5] = 16.944;
    // vertexData[6] = 17.71;
    // vertexData[7] = 0.02;
    // vertexData[8] = -18.717;
    // vertexData[9] = -17.717;
    // vertexData[10] = 0.022;
    // vertexData[11] = -18.455;
    //
    // normalData[0] = 0;
    // normalData[1] = 1;
    // normalData[2] = 0;
    //
    // normalData[3] = 0;
    // normalData[4] = 1;
    // normalData[5] = 0;
    //
    // normalData[6] = 0;
    // normalData[7] = 1;
    // normalData[8] = 0;
    //
    // normalData[9] = 0;
    // normalData[10] = 1;
    // normalData[11] = 0;

// buffer tracing cout datasi
        // cout << "vertexdatastarts" << endl;
        // for (int i=0; i<totalNumVertices; i++)
        // {
        //     cout << vertexData[3*i] << " " << vertexData[3*i+1] << " " << vertexData[3*i+2] << endl;
        // }
        // cout << "normaldatastarts" << endl;
        // for (int i=0; i<totalNumVertices; i++)
        // {
        //     cout << normalData[3*i] << " " << normalData[3*i+1] << " " << normalData[3*i+2] << endl;
        // }
