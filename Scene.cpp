#include "Scene.h"

Scene* CurrentScene;

void Scene::sceneData()
{
    cout << "Printing Scene Data..." << endl;
    cout << "Background Color (RGB): " << _background << endl;
    // cout << "Vertices: " << endl;
    // for(vector<Vertex>::iterator it_ver = _vertices.begin(); it_ver!=_vertices.end(); ++it_ver){cout << *it_ver << endl;}
    cout << "Lights: " << endl;
    for(vector<PointLight>::iterator it_light = _lights.begin(); it_light!=_lights.end(); ++it_light){cout << *it_light << endl;}
    cout << "Materials: " << endl;
    for(vector<Material>::iterator it_mat = _materials.begin(); it_mat!=_materials.end(); ++it_mat){cout << *it_mat << endl;}
    cout << "Translations: " << endl;
    for(vector<Vector3>::iterator it_vea = _translations.begin(); it_vea!=_translations.end(); ++it_vea){cout << *it_vea << endl;}
    cout << "Scalings: " << endl;
    for(vector<Vector3>::iterator it_sca = _scalings.begin(); it_sca!=_scalings.end(); ++it_sca){cout << *it_sca << endl;}
    cout << "Rots: " << endl;
    for(vector<Rotation>::iterator it_rot = _rotations.begin(); it_rot!=_rotations.end(); ++it_rot){cout << *it_rot << endl;}
    cout << "Meshes: " << endl;
    for(vector<Mesh>::iterator it_mod = _meshes.begin(); it_mod!=_meshes.end(); ++it_mod){cout << *it_mod << endl;}
   // cout << "Meshes: " << endl;
   // for(vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); ++it_mesh){cout << *it_mesh << endl;}
    cout << "Cameras: " << endl;
    for(vector<Camera>::iterator it_cam = _cameras.begin(); it_cam!=_cameras.end(); ++it_cam){cout << *it_cam << endl;}
}

void ReadScene(int argc, char** argv)
{
    ifstream scenefile(argv[1]);
    ifstream camerafile(argv[2]);

    string hashtag_vertices;
    string hashtag_colors;
    string hashtag_positions;
    string hashtag_translations;
    string hashtag_scalings;
    string hashtag_rotations;
    string hashtag_meshes;
    int light_id;
    int colx, coly, colz;
    float vecx, vecy, vecz, vecalfa;
    uint indx, indy, indz;
    int vector_count, translation_count;
    int scaling_count, rotation_count;
    int mesh_count, pointlight_count;
    int material_count;
    int temp_count;
    Vector3* tempvec;
    Rotation* temprot;
    Mesh* tempmesh;
    int tempcount;
    int i,j;

    string hashtag_light;
    PointLight* templight;
    Color temp_lightint;

    string hashtag_materials;
    int mat_id;
    Color temp_ambient, temp_diffuse, temp_spec;
    float temp_specexp;
    Material* tempmat;

    if(scenefile)
    {
        CurrentScene = new Scene();
        scenefile >> CurrentScene->_background;
        scenefile >> CurrentScene->_ambient;



        /* ----------lights------------*/

        scenefile >> pointlight_count;
        temp_count = pointlight_count;
        while(temp_count)
        {
            // insert point light
            scenefile >> hashtag_light >> light_id;
            scenefile >> vecx >> vecy >> vecz;
            scenefile >> temp_lightint;
            tempvec = new Vector3(vecx, vecy, vecz);
            templight = new PointLight(*tempvec, temp_lightint);
            CurrentScene->_lights.push_back(*templight);
            temp_count--;
            delete tempvec;
            delete templight;
        }

        /* ------------materials------------*/

        scenefile >> material_count;
        temp_count = material_count;
        while(temp_count)
        {
            scenefile >> hashtag_materials >> mat_id;
            scenefile >> temp_ambient >> temp_diffuse >> temp_spec >> temp_specexp;
            tempmat = new Material(temp_ambient, temp_diffuse, temp_spec, temp_specexp);
            CurrentScene->_materials.push_back(*tempmat);
            delete tempmat;
            temp_count--;
        }

        /*-----------translations----------*/

        scenefile >> hashtag_translations;
        scenefile >> translation_count;
        while(translation_count)
        {
            scenefile >> vecx >> vecy >> vecz;
            tempvec = new Vector3(vecx,vecy,vecz);
            CurrentScene->_translations.push_back(*tempvec);
            delete tempvec;
            translation_count--;
        }

        /*---------scaling---------*/

        scenefile >> hashtag_scalings;
        scenefile >> scaling_count;
        while(scaling_count)
        {
            scenefile >> vecx >> vecy >> vecz;
            tempvec = new Vector3(vecx,vecy,vecz);
            // cout << "scale: " << *tempvec << endl;
            CurrentScene->_scalings.push_back(*tempvec);
            delete tempvec;
            scaling_count--;
        }

        /*---------rotations---------*/

        scenefile >> hashtag_rotations;
        scenefile >> rotation_count;
        // cout << "HASHTAGMODELS: " << hashtag_rotations << endl;

        while(rotation_count)
        {
            // cout << "ROTATIONCOUNT: " << rotation_count << endl;
            scenefile >> vecalfa >> vecx >> vecy >> vecz;
            tempvec = new Vector3(vecx,vecy,vecz);
            temprot = new Rotation(vecalfa, *tempvec);
            // cout << "newrot::" << vecalfa << vecx << vecy << vecz << endl;
            CurrentScene->_rotations.push_back(*temprot);
            delete tempvec;
            delete temprot;
            rotation_count--;
        }

        /*-----------vertices----------*/

        scenefile >> vector_count;
        scenefile >> hashtag_vertices;
        tempcount = vector_count;
        while (tempcount)
        {
            CurrentScene->_vertices.push_back(Vertex());
            tempcount--;
        }

        /*-----------positions----------*/

        i = 0;
        while (i<vector_count)
        {
            scenefile >> vecx >> vecy >> vecz;
            CurrentScene->_vertices[i]._position = Vector3(vecx, vecy, vecz);
            i++;
        }

        ;
        /*---------models---------*/

        scenefile >> mesh_count;
        int meshc = mesh_count;
        vector< pair<char,int> > temp_operations;

        while(mesh_count)
        {
            // cout << "meshcount: " << mesh_count << endl;
            int model_ID;
            int model_type;
            int material_id;
            int op_count;
            int num_of_triangles;

            scenefile >> hashtag_meshes >> model_ID;
            scenefile >> model_type >> material_id;
            /* --- writing operations to mesh's op_array --- */
            scenefile >> op_count;
            temp_count = op_count;
            char temp_char;
            int temp_int;
            while(temp_count)
            {
              scenefile >> temp_char >> temp_int;
              temp_operations.push_back(pair<char,int>(temp_char, temp_int));
              temp_count--;
            }
            // cout << "operations for id [" << model_ID << "]: " << temp_operations.size() << endl;
            /* ------------------------------------- */

            scenefile >> num_of_triangles;
            // cout << "numoftriangles!" << num_of_triangles << endl;
            tempmesh = new Mesh(model_ID, model_type, material_id, num_of_triangles, CurrentScene->_vertices.size(), CurrentScene->_vertices, temp_operations.size(), temp_operations);
            // cout << "numoftriangles!" << num_of_triangles << endl;
            while(num_of_triangles)
            {
                scenefile >> indx >> indy >> indz;
                tempmesh->bitmap[indx-1] = 1;
                tempmesh->bitmap[indy-1] = 1;
                tempmesh->bitmap[indz-1] = 1;
                tempmesh->triplets.push_back(Triplet(indx-1,indy-1,indz-1));
                num_of_triangles--;
            }
            tempmesh->loadIndexBuffer(); // loads triplets into index buffer.
            // cout << "numoftriangleasds!" << num_of_triangles << endl;
            mesh_count--;
            CurrentScene->_meshes.push_back(*tempmesh);
            temp_operations.clear();
            delete tempmesh;
        }
        scenefile.close();
    }
    else
    {
        cout << "error reading scenefile! exiting with status -1..." << endl;
        return;
    }


    Camera* tempcam;
    Vector3* cam_temppos;
    Vector3* cam_tempgaze;
    Vector3* cam_tempup;
    float cam_left, cam_right, cam_bottom, cam_top, cam_near, cam_far;
    int cam_horres, cam_verres;

    if(camerafile)
    {
        camerafile >> vecx >> vecy >> vecz;
        cam_temppos = new Vector3(vecx, vecy, vecz);
        camerafile >> vecx >> vecy >> vecz;
        cam_tempgaze = new Vector3(vecx, vecy, vecz);
        camerafile >> vecx >> vecy >> vecz;
        cam_tempup = new Vector3(vecx, vecy, vecz);
        camerafile >> cam_left >> cam_right >> cam_bottom >> cam_top >> cam_near >> cam_far;
        camerafile >> cam_horres >> cam_verres;
        tempcam = new Camera(*cam_temppos, *cam_tempgaze, *cam_tempup, cam_left, cam_right, cam_bottom, cam_top, cam_near, cam_far, cam_horres, cam_verres);
        CurrentScene->_cameras.push_back(*tempcam);
        delete cam_temppos;
        delete cam_tempgaze;
        delete cam_tempup;
        delete tempcam;
    }


    int mes=0;
    int k=0;
    for(vector<Mesh>::iterator it_mesh=CurrentScene->_meshes.begin(); it_mesh!=CurrentScene->_meshes.end(); it_mesh++)
    {
        // cout << "mesh id: " << mes << endl;
        for(int i=0; i<(*it_mesh)._operations.size(); i++)
        {
            char opkey = (*it_mesh)._operations[i].first;
            int opid = (*it_mesh)._operations[i].second;
            // cout << "opkey: " << opkey << " opid: " << opid << endl;
            if (opkey=='t')
            {
                // cout << "entering translation. uygulanacak translation: " << CurrentScene->_translations[opid-1] << endl;
                k=0;
                while(k<CurrentScene->_vertices.size())
                {
                    if((*it_mesh).bitmap[k])
                    {
                        CurrentScene->_vertices[k]._position = CurrentScene->_vertices[k]._position +
                                                               CurrentScene->_translations[opid-1];
                    }
                    k++;
                }
            }
            if (opkey=='r')
            {
                // cout << "entering rotation. uygulanacak rotation: " << CurrentScene->_rotations[opid-1] << endl;
                k=0;
                while(k<CurrentScene->_vertices.size())
                {
                    if((*it_mesh).bitmap[k])
                    {
                        CurrentScene->_vertices[k]._position = arbitrary_rotate(CurrentScene->_vertices[k]._position,
                                                                            CurrentScene->_rotations[opid-1].alfa,
                                                                            CurrentScene->_rotations[opid-1].rotaxis);
                    }
                    k++;
                }
            }
            if (opkey=='s')
            {
                // cout << "entering scale!. uygulanacak scalitasyon: " << CurrentScene->_scalings[opid-1] << endl;
                k=0;
                while(k<CurrentScene->_vertices.size())
                {
                    if((*it_mesh).bitmap[k])
                    {
                        CurrentScene->_vertices[k]._position._data[0] = CurrentScene->_vertices[k]._position._data[0] * CurrentScene->_scalings[opid-1]._data[0];
                        CurrentScene->_vertices[k]._position._data[1] = CurrentScene->_vertices[k]._position._data[1] * CurrentScene->_scalings[opid-1]._data[1];
                        CurrentScene->_vertices[k]._position._data[2] = CurrentScene->_vertices[k]._position._data[2] * CurrentScene->_scalings[opid-1]._data[2];
                    }
                    k++;
                }
            }
        }

        for(int i=0; i<(*it_mesh).triplets.size(); i++)
        {
            int index_anok = (*it_mesh).triplets[i].one;
            int index_bnok = (*it_mesh).triplets[i].two;
            int index_cnok = (*it_mesh).triplets[i].three;

            Vector3 anoktasi = CurrentScene->_vertices[index_anok]._position;
            Vector3 bnoktasi = CurrentScene->_vertices[index_bnok]._position;
            Vector3 cnoktasi = CurrentScene->_vertices[index_cnok]._position;

            Vector3 n = (crossProduct((bnoktasi-anoktasi), (cnoktasi-anoktasi)));

            CurrentScene->_vertices[index_anok]._normal = CurrentScene->_vertices[index_anok]._normal + n;
            CurrentScene->_vertices[index_bnok]._normal = CurrentScene->_vertices[index_bnok]._normal + n;
            CurrentScene->_vertices[index_cnok]._normal = CurrentScene->_vertices[index_cnok]._normal + n;

            CurrentScene->_vertices[index_anok]._normalcount += 1;
            CurrentScene->_vertices[index_bnok]._normalcount += 1;
            CurrentScene->_vertices[index_cnok]._normalcount += 1;
        }

        mes++;
    }
    for(i=0;i<CurrentScene->_vertices.size(); i++)
    {
        if(CurrentScene->_vertices[i]._normalcount!=0)
        {
            CurrentScene->_vertices[i]._normal = normalize(CurrentScene->_vertices[i]._normal / CurrentScene->_vertices[i]._normalcount);
        }
    }

    for(vector<Mesh>::iterator it_mesh=CurrentScene->_meshes.begin(); it_mesh!=CurrentScene->_meshes.end(); it_mesh++)
    {
        i=0;
        int meshindex = (*it_mesh).model_id-1;
        while(i<(*it_mesh).triplets.size())
        {
            uint a = (*it_mesh).triplets[i].one;
            uint b = (*it_mesh).triplets[i].two;
            uint c = (*it_mesh).triplets[i].three;
            CurrentScene->global_triplets.push_back(Triplet(a,b,c,meshindex));
            i++;
        }
    }

    // cout << "vertices:" << endl;
    // while(i<CurrentScene->_vertices.size())
    // {
    //     cout << "Vertice index" << i << ": " << CurrentScene->_vertices[i]._position << endl;
    //     i++;
    // }
    // cout << "normals:" << endl;
    // while(i<CurrentScene->_vertices.size())
    // {
    //     cout << "Vertice id" << i << ": " << CurrentScene->_vertices[i]._normal << endl;
    //     i++;
    // }
}



/*

void Scene::cameraTransformation(int camera_index)
{
    Vector3 right = _cameras[camera_index]._space.Right;
    Vector3 up = _cameras[camera_index]._space.Up;
    Vector3 minusgaze = _cameras[camera_index]._space.Forward*(-1);
    Vector3 campos = _cameras[camera_index]._position;
    Vector3 temp;
    // cout << "right: " << right << endl;
    // cout << "up: " << up << endl;
    // cout << "minusgaze: " << minusgaze << endl;
    // cout << "campos: " << campos << endl;
    int i;
    for (vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); it_mesh++)
    {
        // cout << "Before camera transformation:" << endl;
        // for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        // {
        //     cout << it_vert->_position << endl;
        // }
        i=0;
        for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        {
        //    if ((*it_mesh).bitmap[i])
        //    {
                temp = (*it_vert)._position;
                // cout << "WorldCoords: " << temp << endl;
                (*it_vert)._position._data[0] = (right*temp) - (right*campos);
                (*it_vert)._position._data[1] = (up*temp) - (up*campos);
                (*it_vert)._position._data[2] = (minusgaze*temp) - (minusgaze*campos);
                // cout << "CameraCoords: " << (*it_vert)._position << endl;
                i++;
        //    }
        }
        // cout << "After camera transformation: " << endl;
        // for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        // {
        //     cout << it_vert->_position << endl;
        // }
        (*it_mesh).loadTriangles();
        // for (i=0; i<12; i++)
        // {
        //     cout << (*it_mesh).triplets[i].one << (*it_mesh).triplets[i].two << (*it_mesh).triplets[i].three << (*it_mesh).triplets[i].exists << endl;
        // }
    }
}

void Scene::projectionTransformation(int camera_index)
{
    // cout <<  "eee" << endl;
    float r = _cameras[camera_index]._imagePlane.Right;
    float l = _cameras[camera_index]._imagePlane.Left;
    float t = _cameras[camera_index]._imagePlane.Top;
    float b = _cameras[camera_index]._imagePlane.Bottom;
    float n = _cameras[camera_index]._imagePlane.Near;
    float f = _cameras[camera_index]._imagePlane.Far;
    float x,y,z;
    // cout << "r: " << r << endl;
    // cout << "l: " << l << endl;
    // cout << "t: " << t << endl;
    // cout << "b: " << b << endl;
    // cout << "n: " << n << endl;
    // cout << "f: " << f << endl;
    int i =0;
    // cout << "i: " << i << endl;
    for (vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); it_mesh++)
    {
        // for(i =0; i<8; i++)
        //     cout << "bitmap[" << i << "]: " << it_mesh->bitmap[i] << endl;
        i=0;
        for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        {
            // cout << "i: " << i << endl;
            // if ((*it_mesh).bitmap[i])
            // {
                x = (*it_vert)._position._data[0];
                y = (*it_vert)._position._data[1];
                z = (*it_vert)._position._data[2];
                // cout << "INITIAL COORDS: " << (*it_vert)._position << endl;
                (*it_vert)._position._data[0] = ((x*2*n)/(r-l) + z*(r+l)/(r-l))/(-1*z);
                (*it_vert)._position._data[1] = ((y*2*n)/(t-b) + -1*z*(t+b)/(t-b))/(-1*z);
                (*it_vert)._position._data[2] = ((-1*z*(f+n)/(f-n) + (-2*f*n)/(f-n)))/(-1*z );
                // if ((*it_vert)._position._data[0]<-1)
                // {
                //     cout << "SEGMENT: " << (*it_vert)._position << endl;
                //     cout << "eskisi: " << x << "__" << y << "__" << z << endl;
                // }
                // cout << "FINAL COORDS: " << (*it_vert)._position << endl;
            // }
            // else{
            //     cout << "SU NOKTA BITMAPTA YOK: " << i << endl;
            // }
            i++;
        }
        // cout << "After projection transformation: " << endl;
        // for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        // {
        //     cout << it_vert->_position << endl;
        // }
        (*it_mesh).loadTriangles();
    }
}

void Scene::viewportTransformation(int camera_index)
{
    int nx = _cameras[camera_index]._imagePlane.Width;
    int ny = _cameras[camera_index]._imagePlane.Height;
    float n = _cameras[camera_index]._imagePlane.Near;
    float f = _cameras[camera_index]._imagePlane.Far;
    // cout << "nx: " << nx << endl;
    // cout << "ny: " << ny << endl;
    // cout << "n: " << n << endl;
    // cout << "f: " << f << endl;
    float x,y,z;
    int i;
    for (vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); it_mesh++)
    {
        // cout << "numoftriangleS: " << (*it_mesh).triangles.size() << endl;
        // cout << "Bitmap: ";
        // for(i=0; i<CurrentScene->_vertices.size(); i++)
        // {
        //     cout << it_mesh->bitmap[i] << " ";
        // }
        // cout << "__EndOfBitmap" << endl;
        i = 0;
        for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        {
            // if ((*it_mesh).bitmap[i])
            // {
                x = (*it_vert)._position._data[0];
                y = (*it_vert)._position._data[1];
                z = (*it_vert)._position._data[2];
                // cout << "INITIAL COORDS: " << (*it_vert)._position << endl;
                (*it_vert)._position._data[0] = (float)(int)(x*nx/2 + (nx-1)/2)+1; // piksel degerleri floored
                (*it_vert)._position._data[1] = (float)(int)(y*ny/2 + (ny-1)/2)+1;
                (*it_vert)._position._data[2] = (z+1)/2;
                // cout << "FINAL COORDS: " << (*it_vert)._position << endl;
            // }
            // else
            // {
            //     // cout << "ZAAAAA BU UCGENDEN YOKMUS BNDE... i: " << i << endl;
            // }

            i++;
        }
        // cout << "sa" << endl;

        // Vector3 a(-1,-1,0);
        // Vector3 b(1,1,1);
        // x = a._data[0];
        // y = a._data[1];
        // z = a._data[2];
        // cout << "INITIAL COORDS of a : " << a << endl;
        // a._data[0] = (float)(int)(x*nx/2 + (nx-1)/2)+1; // piksel degerleri floored
        // a._data[1] = (float)(int)(y*ny/2 + (ny-1)/2)+1;
        // a._data[2] = (z+1)/2;
        // cout << "FINAL COORDS of a : " << a << endl;
        //
        // cout << "After viewport transformation: " << endl;
        // for (vector<Vertex>::iterator it_vert = (*it_mesh).vertices.begin(); it_vert!=(*it_mesh).vertices.end(); it_vert++)
        // {
        //     cout << it_vert->_position << endl;
        // }
        // cout << "numoftriangleS: " << (*it_mesh).triangles.size() << endl;
        // cout << "Bitmap: ";
        // for(i=0; i<CurrentScene->_vertices.size(); i++)
        // {
        //     cout << it_mesh->bitmap[i] << " ";
        // }
        // cout << "__EndOfBitmap" << endl;
        (*it_mesh).loadTriangles();
    }
}

void Scene::cull(int camera_index)
{
    float x,y,z;
    int i;
    Vector3 v,n;
    for (vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); it_mesh++)
    {
        // cout << "pre cull map info:" << endl;
        // for (i=0; i<12; i++)
        // {
        //     cout << (*it_mesh).triplets[i].one << (*it_mesh).triplets[i].two << (*it_mesh).triplets[i].three << (*it_mesh).triplets[i].exists << endl;
        // }
        // cout << "numoftriangleS: " << (*it_mesh).triangles.size() << endl;
        // cout << "Bitmap: ";
        // for(i=0; i<CurrentScene->_vertices.size(); i++)
        // {
        //     cout << it_mesh->bitmap[i] << " ";
        // }
        // cout << "__EndOfBitmap" << endl;
        i = 0;

        vector<Triangle>::iterator it_tri = (*it_mesh).triangles.begin();
        while (it_tri!=(*it_mesh).triangles.end())
        {
            n = normalize(crossProduct(((*it_tri)._b._position-(*it_tri)._a._position), ((*it_tri)._c._position-(*it_tri)._a._position)));
            v = normalize((*it_tri)._a._position - _cameras[camera_index]._position);
            if (n*v>=0)
            {
                // cout << "elencek ucgen buldum! i: " << i << ", coords: " << (*it_tri) << " hatta normali: " << n << endl;
                (*it_mesh).bitmap[(*it_mesh).triplets[i].one]--;
                (*it_mesh).bitmap[(*it_mesh).triplets[i].two]--;
                (*it_mesh).bitmap[(*it_mesh).triplets[i].three]--;
                (*it_mesh).triplets[i].exists = 0;
                (*it_mesh).triangle_count--;
            }
            else
            {
                // cout << "niye eliyim amk? i: " << i << ", n: " << n << ", coords: " << (*it_tri) << ", hatta sonuc: " << n*v << endl;
            }
            i++;
            it_tri++;
        }
        (*it_mesh).loadTriangles();
        // cout << "post cull map info:" << endl;
        // for (i=0; i<12; i++)
        // {
        //     cout << (*it_mesh).triplets[i].one << (*it_mesh).triplets[i].two << (*it_mesh).triplets[i].three << (*it_mesh).triplets[i].exists << endl;
        // }
        // cout << "Bitmap: ";
        // for(i=0; i<CurrentScene->_vertices.size(); i++)
        // {
        //     cout << it_mesh->bitmap[i] << " ";
        // }
        // cout << "__EndOfBitmap" << endl;
        // cout << "Gunun sonunda mesh: " << endl;
        // cout << (*it_mesh) << endl;
    }
}

void Scene::rasterize(int camera_index, Image& img)
{
    // cout << "saa" << endl;
    int i;
    int xmin, xmax, ymin, ymax;
    Vector3 a,b,c;
    float x0,x1,x2,y0,y1,y2;
    float alfa,beta,gama,depth;
    Color color;
    int index;
    for (vector<Mesh>::iterator it_mesh = _meshes.begin(); it_mesh!=_meshes.end(); it_mesh++)
    {
        // cout << "mesh:" << endl;
        // cout << (*it_mesh) << endl;
        i = 0;
        for (vector<Triangle>::iterator it_tri = (*it_mesh).triangles.begin(); it_tri!=(*it_mesh).triangles.end(); it_tri++)
        {
            // cout << "modelid:" << (*it_mesh).model_type << endl;
            if((*it_mesh).model_type==1)
            {
                a = (*it_tri)._a._position;
                b = (*it_tri)._b._position;
                c = (*it_tri)._c._position;
                x0 = (*it_tri)._a._position._data[0];
                x1 = (*it_tri)._b._position._data[0];
                x2 = (*it_tri)._c._position._data[0];
                y0 = (*it_tri)._a._position._data[1];
                y1 = (*it_tri)._b._position._data[1];
                y2 = (*it_tri)._c._position._data[1];


                xmin = std::min(a.x(), std::min(b.x(), c.x()));
                xmax = std::max(a.x(), std::max(b.x(), c.x()));
                ymin = std::min(a.y(), std::min(b.y(), c.y()));
                ymax = std::max(a.y(), std::max(b.y(), c.y()));

                // cout << "a: " << a << endl;
                // cout << "b: " << b << endl;
                // cout << "c: " << c << endl;
                // cout << "x0: " << x0 << endl;
                // cout << "x1: " << x1 << endl;
                // cout << "x2: " << x2 << endl;
                // cout << "y0: " << y0 << endl;
                // cout << "y1: " << y1 << endl;
                // cout << "y2: " << y2 << endl;
                // cout << "xmin,max: " << xmin << " " << xmax << endl;
                // cout << "ymin,max: " << ymin << " " << ymax << endl;

                for (int y=ymin; y<=ymax; y++)
                {
                    for (int x=xmin; x<=xmax; x++)
                    {
                        // cout << "xmin: " << xmin;
                        // cout << " xmax: " << xmax;
                        // cout << " ymin: " << ymin;
                        // cout << " ymax: " << ymax << endl;
                        alfa = (*it_tri).f_12(x,y)/(*it_tri).f_12(x0,y0);
                        beta = (*it_tri).f_20(x,y)/(*it_tri).f_20(x1,y1);
                        gama = (*it_tri).f_01(x,y)/(*it_tri).f_01(x2,y2);
                        if (alfa>=0 && beta>=0 && gama>=0)
                        {
                            // cout << "ALFA: " << alfa << " BETA: " << beta << " GAMA: " << gama << endl;
                            color = (*it_tri)._a._color*alfa + (*it_tri)._b._color*beta + (*it_tri)._c._color*gama;
                            depth = (*it_tri)._a._position.z()*alfa + (*it_tri)._b._position.z()*beta + (*it_tri)._c._position.z()*gama;
                            // cout << "color: " << color;
                            // cout << " depth: " << depth;
                            // cout << " SU ANKI X Y: " << x << " " << y;
                            // cout << " INDEXIM: " << y*(img._width)+x << endl;
                            index = (img._height-1-y)*(img._width)+x;
                            if (index>=0 || index<img._height*img._width)
                            {
                                if (depth < img._buffer[(img._height-1-y)*(img._width)+x])
                                {
                                    // cout << "d_old: " << img._buffer[y*(img._width+x)] << " new: " << depth << endl;
                                    img._pixels[(img._height-1-y)*(img._width)+x] = color;
                                    img._buffer[(img._height-1-y)*(img._width)+x] = depth;
                                }
                            }
                            else
                            {
                                cout << "yoh" << endl;
                            }
                        }
                    }
                }
            }

            else if ((*it_mesh).model_type == 2) // wireframe rasterization
            {
                // int E;
                // E=0;
                for (vector<Triangle>::iterator it_tri = (*it_mesh).triangles.begin(); it_tri!=(*it_mesh).triangles.end(); it_tri++)
                {
                    // cout << "linedraw! current ucgen: " << (*it_tri) << endl;
                    Vertex a = (*it_tri)._a;
                    Vertex b = (*it_tri)._b;
                    Vertex c = (*it_tri)._c;
                    // cout << a << " ile " << b << " arasini ciziyorum: " << endl;
                    drawLine(a,b, img);
                    // cout << b << " ile " << c << " arasini ciziyorum: " << endl;
                    drawLine(b,c, img);
                    // cout << c << " ile " << c << " arasini ciziyorum: " << endl;
                    drawLine(c,a, img);
                }
            }
            // else
            // {
            //     cout << "invalid model id!" << endl;
            //     return;
            // }
        }
    }
}


void Scene::drawLine(Vertex a, Vertex b, Image& img)
{
    Vertex solalt, sagust;
  float x0,y0,x1,y1;
  int index;
    if (a._position.x() < b._position.x())
    {
      solalt = a;
      sagust = b;
    //   x1 = b._position.x();
    //   y1 = b._position.y();
    }
    if (a._position.x() > b._position.x())
    {
    //   x0 = b._position.x();
    //   y0 = b._position.y();
    //   x1 = a._position.x();
    //   y1 = a._position.y();
    solalt= b;
    sagust=a;
    }
    if (a._position.x() == b._position.x())
    {
      if (a._position.y() < b._position.y())
        {
        //   x0 = a._position.x();
        //   y0 = a._position.y();
        //   x1 = b._position.x();
        //   y1 = b._position.y();
        solalt = a;
        sagust= b;
        }
      else
        {
        //   x0 = b._position.x();
        //   y0 = b._position.y();
        //   x1 = a._position.x();
        //   y1 = a._position.y();
        solalt = b;
        sagust = a;
        }
    }
    x0 = solalt._position.x();
    y0 = solalt._position.y();
    x1 = sagust._position.x();
    y1 = sagust._position.y();
    // cout << "entered drawline" << endl;
    Color c0,c1,color;
    float aa,bb,d,incr,depth,m;
    int x,y;
    if (x1==x0)
    {
        m = 999;
    }
    else
    {
        m = (y1-y0)/(x1-x0);
    }

    // cout << "slope: " << m << endl;
    if(m>1)
    {
        // cout << "slope 1den buyuk: " << m << endl;
        d = (x0-x1)+0.5*(y1-y0);
        x = x0;
        c0 = solalt._color;
        c1 = sagust._color;
        incr = 0;

        for (y=y0; y<=y1; y++)
        {
            depth = solalt._position.z()*(1-incr) + sagust._position.z()*incr;
            index = (img._height-1-y)*(img._width)+x;
            if (index>=0 || index<img._height*img._width)
            {
                if (depth < img._buffer[(img._height-1-y)*(img._width)+x])
                {
                    img._buffer[(img._height-1-y)*(img._width)+x] = depth;
                    img._pixels[(img._height-1-y)*(img._width)+x] = c0*(1-incr)+c1*(incr);
                }
            }
            else{
                cout << "asd" << endl;
            }
            if(d<0)
            {
                x++;
                d+=(x0-x1)+(y1-y0);
            }
            else
            {
                d+=(x0-x1);
            }
            incr += 1/(y1-y0);
        }
    }
    else if (m>=0 && m<=1)
    {
        // cout << "slope sifirbir arasi: " << m << endl;
        d = (y0-y1)+0.5*(x1-x0);
        y = y0;
        c0 = solalt._color;
        c1 = sagust._color;
        incr = 0;
        for (x=x0; x<=x1; x++)
        {
            // cout << "x: " << x << "__________y: " << y << endl;
            depth = solalt._position.z()*(1-incr) + sagust._position.z()*incr;
            index = (img._height-1-y)*(img._width)+x;
            if (index>=0 || index<img._height*img._width)
            {
                if (depth < img._buffer[(img._height-1-y)*(img._width)+x])
                {
                    img._buffer[(img._height-1-y)*(img._width)+x] = depth;
                    img._pixels[(img._height-1-y)*(img._width)+x] = c0*(1-incr)+c1*(incr);
                }
            }
            else{
                cout << "asd" << endl;
            }
            if(d<0)
            {
                y++;
                d+=(y0-y1)+(x1-x0);
            }
            else
            {
                d+=(y0-y1);
            }
            incr += 1/(x1-x0);
        }
    }
    else if (m>=-1 && m<0)
    {
        // cout << "slope sifir eksibir arasi: " << m << endl;
        d = (y1-y0)+0.5*(x1-x0);
        y = y0;
        c0 = solalt._color;
        c1 = sagust._color;
        incr = 0;
        for (x=x0; x<=x1; x++)
        {
            depth = solalt._position.z()*(1-incr) + sagust._position.z()*incr;
            index = (img._height-1-y)*(img._width)+x;
            if (index>=0 || index<img._height*img._width)
            {
                if (depth < img._buffer[(img._height-1-y)*(img._width)+x])
                {
                    img._buffer[(img._height-1-y)*(img._width)+x] = depth;
                    img._pixels[(img._height-1-y)*(img._width)+x] = c0*(1-incr)+c1*(incr);
                }
            }
            else{
                cout << "asd" << endl;
            }
            if(d<0)
            {
                y--;
                d+=(y1-y0)+(x1-x0);
            }
            else
            {
                d+=(y1-y0);
            }
            incr += 1/(x1-x0);
        }
    }
    else if (m<-1)
    {
        // cout << "slope eksilede: " << m << endl;
        d = (x0-x1)+0.5*(y0-y1);
        x = x0;
        c0 = solalt._color;
        c1 = sagust._color;
        incr = 0;
        for (y=y0; y>=y1; y--)
        {
            depth = solalt._position.z()*(1-incr) + sagust._position.z()*incr;
            index = (img._height-1-y)*(img._width)+x;
            if (index>=0 || index<img._height*img._width)
            {
                if (depth < img._buffer[(img._height-1-y)*(img._width)+x])
                {
                    img._buffer[(img._height-1-y)*(img._width)+x] = depth;
                    img._pixels[(img._height-1-y)*(img._width)+x] = c0*(1-incr)+c1*(incr);
                }
            }
            else{
                cout << "asd" << endl;
            }
            if(d<0)
            {
                x++;
                d+=(x0-x1)+(y0-y1);
            }
            else
            {
                d+=(x0-x1);
            }
            incr += 1/(y0-y1);
        }
    }
}


/*-----------colors----------*/
//
// scenefile >> hashtag_colors;
// i = 0;
// while(i<vector_count)
// {
//     scenefile >> colx >> coly >> colz;
//     CurrentScene->_vertices[i]._color = Color(colx, coly, colz);
//     i++;
// }

// cout << "HASHTAGMODELS: " << hashtag_models << endl;
// cout << "count: " << model_count << endl

// cout << "MESH ID: " << model_ID << "Bitmap: ";
// for(i=0; i<CurrentScene->_vertices.size(); i++)
// {
//     cout << tempmesh->bitmap[i] << " ";
// }
// cout << "__EndOfBitmap" << endl;
// i=0;
// j=0;
// char op;
// int ind;
// cout << "opcount: " <<op_count << endl;
/*while(j<op_count)
{
// do operations
op = CurrentScene->_operations[j].first;
ind = CurrentScene->_operations[j].second;
// cout << "j: " << j << " op: " << op << " ind: " << ind << endl;
if (op=='t')
{
i=0;
while (i<tempmesh->vertices.size())
{
// if(tempmesh->bitmap[i])
// {
tempmesh->vertices[i]._position = tempmesh->vertices[i]._position + CurrentScene->_translations[ind-1];
// }
i++;
}
}
if (op=='r')
{
i=0;
while (i<tempmesh->vertices.size())
{
// if(tempmesh->bitmap[i])
// {
// cout << "initial coords: " << tempmesh->vertices[i]._position << endl;
tempmesh->vertices[i]._position = arbitrary_rotate(tempmesh->vertices[i]._position, CurrentScene->_rotations[ind-1].alfa, CurrentScene->_rotations[ind-1].rotaxis);
// cout << "final coords: " << tempmesh->vertices[i]._position << endl;
// }
i++;
}
}
if (op=='s')
{
i=0;
// cout << "scale me baby" << endl;
while (i<tempmesh->vertices.size())
{
// cout << "data0: " << CurrentScene->_scalings[ind-1]._data[0];
// if(tempmesh->bitmap[i])
// {
// cout << "ov yeah.." << endl;
tempmesh->vertices[i]._position._data[0] = tempmesh->vertices[i]._position._data[0] * CurrentScene->_scalings[ind-1]._data[0];
tempmesh->vertices[i]._position._data[1] = tempmesh->vertices[i]._position._data[1] * CurrentScene->_scalings[ind-1]._data[1];
tempmesh->vertices[i]._position._data[2] = tempmesh->vertices[i]._position._data[2] * CurrentScene->_scalings[ind-1]._data[2];
// }
i++;
}
}
j++;
}*/

//tempmesh->loadTriangles();
// for (i=0; i<12; i++)
// {
//     cout << tempmesh->triplets[i].one << " " << tempmesh->triplets[i].two << " " << tempmesh->triplets[i].three << " " tempmesh->triplets[i].exists << endl;
// }
// cout << "TEMPMESH ADDTRIANGLES PING" << endl;
