#include "base.h"

// Here we are adding   codes for measuring distance between points,
// distance between two lines,
// vector operator codes etc.

// dot product of two vectors : v1 . v2

void point3D::get(double a, double b, double c)
{
    this->px = a;
    this->py = b;
    this->pz = c;
}

void point3D::get(int a, int b, int c)
{
    this->px = (double)a;
    this->py = (double)b;
    this->pz = (double)c;
}

point3D point3D::operator+(const point3D& p)
{
    point3D pnew;
    pnew.px = this->px + p.px;
    pnew.py = this->py + p.py;
    pnew.pz = this->pz + p.pz;
    return pnew;
}

point3D point3D::operator+(const Vector& p)
{
    point3D pnew;
    pnew.px = this->px + p.x;
    pnew.py = this->py + p.y;
    pnew.pz = this->pz + p.z;
    return pnew;
}

point3D point3D::operator-(const point3D& p)
{
    point3D pnew;
    pnew.px = this->px - p.px;
    pnew.py = this->py - p.py;
    pnew.pz = this->pz - p.pz;
    return pnew;
}

point3D point3D::operator-(const Vector& p)
{
    point3D pnew;
    pnew.px = this->px - p.x;
    pnew.py = this->py - p.y;
    pnew.pz = this->pz - p.z;
    return pnew;
}

void Vector::get(int a, int b, int c)
{
    this->x = (double)a;
    this->y = (double)b;
    this->z = (double)c;
}

void Vector::get(double a, double b, double c)
{
    this->x = a;
    this->y = b;
    this->z = c;
}

Vector Vector::operator+(const Vector& v)
{
    Vector vnew;
    vnew.x = this->x + v.x;
    vnew.y = this->y + v.y;
    vnew.z = this->z + v.z;
    return vnew;
}

Vector Vector::operator-(const Vector& v)
{
    Vector vnew;
    vnew.x = this->x - v.x;
    vnew.y = this->y - v.y;
    vnew.z = this->z - v.z;
    return vnew;
}

Vector Vector::operator*(const int& scalar)
{
    Vector vnew;
    vnew.x = scalar * this->x;
    vnew.y = scalar * this->y;
    vnew.z = scalar * this->z;
}

Vector Vector::operator*(const double& scalar)
{
    Vector vnew;
    vnew.x = scalar * this->x;
    vnew.y = scalar * this->y;
    vnew.z = scalar * this->z;
}

inline double vec_dot(Vector v1, Vector v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

// norm of a Vector
inline double vec_norm(Vector v)
{
    return sq(vec_dot(v, v));
}
