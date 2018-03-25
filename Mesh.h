#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include "Triangle.h"
#include <vector>

using namespace std;


class Triplet
{
	public:
		uint one, two, three;
		int meshindex;
		Triplet(uint a, uint b, uint c): one(a), two(b), three(c) {}
		Triplet(uint a, uint b, uint c, int modelid): one(a), two(b), three(c), meshindex(modelid) {}
};

class Rotation
{
	public:
		float alfa;
		Vector3 rotaxis;
		Rotation(float a, Vector3 _rotaxis): alfa(a), rotaxis(_rotaxis){}
		friend ostream& operator<<(ostream& os, Rotation& rot)
		{
			os << "alfa: " << rot.alfa << " axis:" << rot.rotaxis;
			return os;
		}
};


class Mesh {


	public:
	uint buffer_id;
	int model_id;
	int material_id;
	int model_type;
	int triangle_cap;
	int triangle_count;
	int* bitmap;
	int bitmap_capacity;
	int cap_operations;
	vector<Triangle> triangles;
	// vector<Vertex> vertices;
	vector<Triplet> triplets;
	vector< pair<char, int> > _operations;
	uint* indexBuffer;

		Mesh(int modelid, int modeltype, int matid, int tricount, int capVertices, vector<Vertex> _vert, int capOps, vector< pair<char,int> > _ops)
		{
			_operations.clear();
			triangles.clear();
			triplets.clear();
			model_id = modelid;
			model_type = modeltype;
			material_id = matid;
			triangle_count = tricount;
			triangle_cap = tricount;
			triangles.resize(triangle_count);
			buffer_id=0;
			bitmap_capacity = capVertices;
			bitmap = new int[bitmap_capacity];
			int i=0;
			while (i<capVertices)
			{
				bitmap[i] = 0; // set bitmap
				// vertices.push_back(_vert[i]); // duplicate vertex array into mesh
				i++;
			}
			i=0;
			cap_operations = capOps;
			while(i<capOps)
			{
				_operations.push_back(_ops[i]);
				i++;
			}
		}

		void loadIndexBuffer()
		{
			// cout << "loadindex starts." << endl;
			int indexSize = triplets.size();
			// cout << "indexsize: " << sizeof(uint)*3*indexSize << endl;
			indexBuffer = (uint*)malloc(sizeof(uint)*3*indexSize);
			// cout << "mallocsize: " << sizeof(uint)*indexSize*3 << endl;
			int i = 0;
			while(i<indexSize)
			{
				// cout << "while icinde: " << triplets[i].one << triplets[i].two << triplets[i].three << endl;
				indexBuffer[3*i] = (uint)triplets[i].one;
				indexBuffer[3*i+1] = (uint)triplets[i].two;
				indexBuffer[3*i+2] = (uint)triplets[i].three;
				i++;
			}
			// i=0;
			// while(i<6){cout<<indexBuffer[i];i++;}
		}

		// void loadTriangles()
		// {
		// 	int i=0;
		// 	triangles.clear();
		// 	// cout << "MESH ICI TRIANGLE COUNT: "	 << triangle_count << endl;
		// 	while (i<triangle_cap)
		// 	{
		// 		if (triplets[i].exists)
		// 		{
		// 			triangles.push_back(Triangle(vertices[triplets[i].one], vertices[triplets[i].two], vertices[triplets[i].three]));
		// 		}
		// 		i++;
		// 	}
		// }

		// void AddTriangle(Vector3 v1, Vector3 v2, Vector3 v3)
		// {
		// 	Triangle a(v1,v2,v3,material_id);
		// 	triangles.push_back(a);
		// }

		friend ostream& operator<<(ostream& os, Mesh& mesh)
		{
			os << "triangle count: " << mesh.triangle_count << endl;
			os << "operations (" << mesh._operations.size() << "):" << endl;
			int i=0;
			for(vector< pair<char,int> >::iterator op_it = mesh._operations.begin(); op_it!=mesh._operations.end(); op_it++)
			{
				os << i << ": " << (*op_it).first << " " << (*op_it).second << endl;
			}
			os << "operations ended!" << endl;
			os << "material id: " << mesh.material_id << endl;
			return os;
 		}
		/*
    void Intersect(const Ray& ray, RayHitInfo& hitInfo)
    {
    	for(vector<Triangle>::iterator it_tri = triangles.begin(); it_tri!=triangles.end(); ++it_tri)
    	{
    		(*it_tri).Intersect(ray, hitInfo);
    	}
    }*/
};

#endif //RAYTRACER_MESH_H
