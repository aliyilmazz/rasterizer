#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

class PointLight {


public:
	Vector3 light_position;
	Color light_intensity;

	PointLight(Vector3 _pos, Color _int): light_position(_pos), light_intensity(_int) {}
	Vector3 lpos(){return light_position;}
	Color& lint(){return light_intensity;}
	friend std::istream& operator>>(std::istream& stream, PointLight& light)
	{
		return stream >> light.light_position >> light.light_intensity;
	}
	friend std::ostream& operator<<(std::ostream& os, PointLight& light)
	{
		os << light.lpos() << " || " << light.lint();
		return os;
	}

};

#endif //RAYTRACER_POINTLIGHT_H
