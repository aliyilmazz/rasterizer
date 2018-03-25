#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include <iostream>
#include <fstream>
#include <cmath>


class Vector3
{

public:

    float _data[3];
    Vector3()
    {
    	_data[0]=0;
    	_data[1]=0;
    	_data[2]=0;
    }

    Vector3(float a, float b, float c)
    {
    	_data[0]=a; _data[1]=b; _data[2]=c;
    }

    Vector3(const Vector3& rhs)
    {
    	_data[0]=rhs.x();
    	_data[1]=rhs.y();
    	_data[2]=rhs.z();
    }

    float x() const{return _data[0];}
    float y() const{return _data[1];}
    float z() const{return _data[2];}
    void setx(float _x){_data[0]=_x;}
    void sety(float _y){_data[1]=_y;}
    void setz(float _z){_data[2]=_z;}

    friend std::istream &operator>>(std::istream &stream, Vector3& vec)
    {
        return stream >> vec._data[0]
                      >> vec._data[1]
                      >> vec._data[2];
    }

    friend std::ostream &operator<<(std::ostream &os, Vector3 myVec)
    {
    	os << "(" << myVec.x() << "," << myVec.y() << "," << myVec.z() << ")";
    	return os;
    }

    friend Vector3 operator*(const Vector3& myVec, float mult)
    {
    	Vector3 ret;
    	ret.setx(myVec.x()*mult);
    	ret.sety(myVec.y()*mult);
    	ret.setz(myVec.z()*mult);
    	return ret;
    }

    friend Vector3 operator/(const Vector3& myVec, float divv)
    {
        Vector3 ret;
        ret.setx(myVec.x()/divv);
        ret.sety(myVec.y()/divv);
        ret.setz(myVec.z()/divv);
        return ret;
    }

    friend float operator*(const Vector3& _vec1, const Vector3& _vec2)
    {
        return _vec1.x()*_vec2.x()+
               _vec1.y()*_vec2.y()+
               _vec1.z()*_vec2.z();
    }

    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        Vector3 ret;
        ret.setx(lhs.x()+rhs.x());
        ret.sety(lhs.y()+rhs.y());
        ret.setz(lhs.z()+rhs.z());
        return ret;
     }

    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        Vector3 ret;
        ret.setx(lhs.x()-rhs.x());
        ret.sety(lhs.y()-rhs.y());
        ret.setz(lhs.z()-rhs.z());
        return ret;
    }

};


inline Vector3 crossProduct(Vector3 a, Vector3 b)
{
    Vector3 r;
    r.setx(a.y()*b.z()-a.z()*b.y());
    r.sety(a.z()*b.x()-a.x()*b.z());
    r.setz(a.x()*b.y()-a.y()*b.x());
    return r;
}


inline float vectorDistance(Vector3 a, Vector3 b)
{
    return sqrt(pow((a.x()-b.x()),2) +
                pow((a.y()-b.y()),2) +
                pow((a.z()-b.z()),2)); // kök x2 y2 z2
}

inline float vectorLength(Vector3 victim)
{
    return sqrt(victim.x()*victim.x() +
                victim.y()*victim.y() +
                victim.z()*victim.z()); // kök x2 y2 z2
}

inline Vector3 normalize(Vector3 victim)
{
    return victim/(vectorLength(victim));
}

inline float sinus(Vector3 a, Vector3 b)
{
    Vector3 cp = crossProduct(a,b);
    float ret = vectorLength(cp)/(vectorLength(a)*vectorLength(b));
    return ret;
}

inline Vector3 arbitrary_rotate(Vector3 victim, float theta, Vector3 myaxis)
{
    Vector3 axis = normalize(myaxis);
    float ux = axis.x();
    float uy = axis.y();
    float uz = axis.z();

    float cosQ = cos(theta*M_PI/180);
    float sinQ = sin(theta*M_PI/180);

    float a1 = cosQ + pow(ux,2)*(1-cosQ);
    float a2 = ux*uy*(1-cosQ) - uz*sinQ;
    float a3 = ux*uz*(1-cosQ) + uy*sinQ;

    float b1 = uy*ux*(1-cosQ) + uz*sinQ;
    float b2 = cosQ + pow(uy,2)*(1-cosQ);
    float b3 = uy*uz*(1-cosQ) - ux*sinQ;

    float c1 = uz*ux*(1-cosQ) - uy*sinQ;
    float c2 = uz*uy*(1-cosQ) + ux*sinQ;
    float c3 = cosQ + pow(uz,2)*(1-cosQ);

    Vector3 retVector(0,0,0);
    retVector._data[0] = victim.x()*a1 + victim.y()*a2 + victim.z()*a3;
    retVector._data[1] = victim.x()*b1 + victim.y()*b2 + victim.z()*b3;
    retVector._data[2] = victim.x()*c1 + victim.y()*c2 + victim.z()*c3;
    return retVector;
}


#endif //MATH_VECTOR3_H
