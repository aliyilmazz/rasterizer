#include "Camera.h"
#include "Scene.h"
#include <climits>
/*
bool intersectsWithMesh(Ray lightray)
{
	RayHitInfo hitinfo;
	hitinfo.golgeflag = 1;
	for(vector<Mesh>::iterator it_mesh = CurrentScene->_meshes.begin(); it_mesh!=CurrentScene->_meshes.end(); ++it_mesh)
	{
		for(vector<Triangle>::iterator it_tri = (*it_mesh).triangles.begin(); it_tri!=(*it_mesh).triangles.end(); ++it_tri)
		{
			if ((*it_tri).Intersect(lightray, hitinfo))
				return true;
		}
	}
	return false;
}
*/
/*

inline Color computeColor(RayHitInfo& hitinfo, Vector3 v)
{
 			float totallight_R = 0.0;
			float totallight_G = 0.0;
			float totallight_B = 0.0;
			//lighttan noktaya distance.

			// normal (N -unitvector)
			Vector3 _N = hitinfo.Normal;
			// kamera-nokta (V -unitvector)
			Vector3 _V = v;
		//	if (_N*_V < 0) {_N = _N * -1;}

			totallight_R += CurrentScene->_materials[hitinfo.material_id-1].ambient.R() * CurrentScene->_ambient.R();
			totallight_G += CurrentScene->_materials[hitinfo.material_id-1].ambient.G() * CurrentScene->_ambient.G();
			totallight_B += CurrentScene->_materials[hitinfo.material_id-1].ambient.B() * CurrentScene->_ambient.B();


			for (const auto& mylight : CurrentScene->Lights())
			{
				// distance between light and hitpos
				float dlight = vectorDistance(mylight.light_position,hitinfo.Position);

				Ray lightray(hitinfo.Position+(mylight.light_position-hitinfo.Position)*0.0001, mylight.light_position-hitinfo.Position);


				if (intersectsWithMesh(lightray) || intersectsWithSphere(lightray))
				{
					continue;
				}


				float dlight4314 = 12.56*dlight*dlight;
				// light-nokta (L -unitvector)
				Vector3 _L = normalize(mylight.light_position-hitinfo.Position);
				// H (Phong Yansıması) (V+L -unitvector)
				Vector3 _H = normalize(_V+_L);

					// Intensity = int_katsayisi / 4*pi*dkare
				float __Ir = mylight.light_intensity.R() / dlight4314;
				float __Ig = mylight.light_intensity.G() / dlight4314;
				float __Ib = mylight.light_intensity.B() / dlight4314;

				// diffuse coefficients (r,g,b)
				float __kdr = CurrentScene->_materials[hitinfo.material_id-1].diffuse.R();
				float __kdg = CurrentScene->_materials[hitinfo.material_id-1].diffuse.G();
				float __kdb = CurrentScene->_materials[hitinfo.material_id-1].diffuse.B();


				float NL = _N*_L;
				totallight_R += __kdr * __Ir * max(0.0f, NL);
				totallight_G += __kdg * __Ig * max(0.0f, NL);
				totallight_B += __kdb * __Ib * max(0.0f, NL);

				totallight_R += CurrentScene->_materials[hitinfo.material_id-1].specular.R() * __Ir * pow(max(0.0f,(_N*_H)),CurrentScene->_materials[hitinfo.material_id-1].specexp);
				totallight_G += CurrentScene->_materials[hitinfo.material_id-1].specular.G() * __Ig * pow(max(0.0f,(_N*_H)),CurrentScene->_materials[hitinfo.material_id-1].specexp);
				totallight_B += CurrentScene->_materials[hitinfo.material_id-1].specular.B() * __Ib * pow(max(0.0f,(_N*_H)),CurrentScene->_materials[hitinfo.material_id-1].specexp);
			}

				Color totallight(totallight_R, totallight_G, totallight_B);
				return totallight;
}*/


/*
Color rayTrace(Ray& cameraray, int refl_count)
{
	RayHitInfo hitinfo;
	hitinfo.golgeflag = 0;
	hitinfo.Parameter = LONG_MAX;
	for(vector<Sphere>::iterator it_sph = CurrentScene->_spheres.begin(); it_sph!=CurrentScene->_spheres.end(); ++it_sph)
	{
		(*it_sph).Intersect(cameraray, hitinfo);
	}
	for(vector<Mesh>::iterator it_mesh = CurrentScene->_meshes.begin(); it_mesh!=CurrentScene->_meshes.end(); ++it_mesh)
	{
		(*it_mesh).Intersect(cameraray, hitinfo);
	}
	if (hitinfo.Parameter < LONG_MAX)
	{
		Vector3 d = normalize(cameraray.Direction());
		if (refl_count==0 || (CurrentScene->_materials[hitinfo.material_id-1].reflectance.R() == 0 &&
			                 CurrentScene->_materials[hitinfo.material_id-1].reflectance.G() == 0 &&
			                 CurrentScene->_materials[hitinfo.material_id-1].reflectance.B() == 0) )
		{
			return computeColor(hitinfo, d*(-1));
		}
		else
		{
			Vector3 reflvec = normalize(d-hitinfo.Normal*2*(d*hitinfo.Normal));
			Ray recursiveray(hitinfo.Position + (reflvec)*(sinus(hitinfo.Normal, d)/70), reflvec);
			return computeColor(hitinfo,d*(-1)) + CurrentScene->_materials[hitinfo.material_id-1].reflectance*rayTrace(recursiveray, refl_count-1);
		}
	}
	else
	{
		// cout << "B";
		return CurrentScene->_background;
	}
}
*/
Image Camera::Render() const
{
	int width = _imagePlane.Width;
	int height = _imagePlane.Height;
	// cout << "Renderdayim. W-H: " << width << "-" << height << endl;
	Image img(width, height, CurrentScene->_background);
	// cout << "OLUSTURDUGUM X Y : " <<  width << " " << height << endl;
	/*CurrentScene->cameraTransformation(camera_id);
	// cout << "camera transformation ended" << endl;
	// cout << "AFTER CAMERA TRANSFORMATION !!!!!" << endl;
	// CurrentScene->sceneData();
	CurrentScene->cull(camera_id);
	// cout << "cull ended" << endl;
	CurrentScene->projectionTransformation(camera_id);
	// cout << "AFTER PROJ TRANSFORMATION !!!!!" << endl;
	// CurrentScene->sceneData();
	// cout << "AFTER CULL!" << endl;
	// CurrentScene->sceneData();
	// cout << "projection transformation ended" << endl;
	CurrentScene->viewportTransformation(camera_id);
	// cout << "viewport transformation ended" << endl;
	// cout << "###########AFTER WP TRANSFORMATION !!!!!";
	// cout << "###########_________AFTER WP TRANSFORMATION !!!!!";
	// CurrentScene->sceneData();
	CurrentScene->rasterize(camera_id, img);
	// cout << "rasterize ended" << endl;
	// CurrentScene->sceneData();
	*/
	return img;
}
