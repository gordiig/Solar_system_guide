#include "obj.h"

Obj::Obj(const Obj &in)
{
    (*this) = in;
}
Obj::Obj(Obj &&in)
{
    (*this) = in;
    in.clear();
}
Obj& Obj::operator = (const Obj& in)
{
    clear();

    points = in.points;
    poly = in.poly;

    return *this;
}
Obj& Obj::operator = (Obj&& in)
{
    clear();

    points = in.points;
    poly = in.poly;

    in.clear();

    return *this;
}

Obj::Obj(const Points3D &in_1, const PolyList &in_2)
{
    points = in_1;
    poly = in_2;
}
Obj::Obj(Points3D &&in_1, PolyList &&in_2)
{
    points = in_1;
    poly = in_2;

    in_1.clear();
    for (auto &x : in_2)
    {
        x.clear();
    }
    in_2.clear();
}

Obj::~Obj()
{
    this->clear();
}

void Obj::clear()
{
    points.clear();
    for (auto &x : poly)
    {
        x.clear();
    }
    poly.clear();
}
Points3D Obj::makeCut(int i) const
{
    Points3D ans;
    for (auto &x : poly[i])
    {
        ans.push_back(points[x-1]);
    }

    return ans;
}

MathVector Obj::calcInNorm(const int i) const
{
    return calcInNorm(makeCut(i));
}
MathVector Obj::calcOutNorm(const int i) const
{
    return calcOutNorm(makeCut(i));
}

std::vector<MathVector> Obj::calcPointNorm(const int poly_num) const
{
    std::vector<MathVector> ans;

    for (auto &x : poly[poly_num])
    {
        ans.push_back(MathVector(points[x-1].x, points[x-1].y, points[x-1].z));
    }

    return ans;
}

Obj Sphere::obj;

Sphere::Sphere() : VisibleObject::VisibleObject() { }
Sphere::Sphere(const double in_x, const double in_y, const double in_z) :
    VisibleObject::VisibleObject(in_x, in_y, in_z) { }
Sphere::Sphere(const double in_x, const double in_y, const double in_z,
               const double in_x_ang, const double in_y_ang, const double in_z_ang) :
    VisibleObject::VisibleObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang) { }
Sphere::Sphere(const double in_x, const double in_y, const double in_z,
               const double in_x_ang, const double in_y_ang, const double in_z_ang,
               const int in_kd, const int in_ka) :
    VisibleObject::VisibleObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang, in_kd, in_ka) { }
Sphere::Sphere(Dot3D<double> &in) : VisibleObject::VisibleObject(in) { }
Sphere::Sphere(Dot3D<double> &in, int in_1, int in_2) : VisibleObject::VisibleObject(in, in_1, in_2) { }
Sphere::Sphere(Dot3D<int> &in) : VisibleObject::VisibleObject(in) { }
Sphere::Sphere(Dot3D<int> &in, int in_1, int in_2) : VisibleObject::VisibleObject(in, in_1, in_2) { }
Sphere::Sphere(const std::vector<Dot3D<double> > &in_points, const std::vector<std::list<int> > &in_poly)
{
    Obj tmp(in_points, in_poly);
    obj = tmp;
}
Sphere::Sphere(std::vector<Dot3D<double> > &&in_points, std::vector<std::list<int> > &&in_poly)
{
    Obj tmp(in_points, in_poly);
    obj = tmp;

    in_points.clear();
    for (auto &x : in_poly)
    {
        x.clear();
    }
    in_poly.clear();
}

Sphere::Sphere(const Sphere &in)
{
    (*this) = in;
}
Sphere::Sphere(Sphere &&in)
{
    (*this) = in;

    in.clear();
}
Sphere& Sphere::operator = (const Sphere& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;

    return (*this);
}
Sphere &Sphere::operator = (Sphere&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;

    in.clear();

    return (*this);
}

Dot3D<double>& Sphere::operator [] (int i) const
{
    return obj.points[i];
}

void Sphere::clear()
{
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
    ka = 0;
    kd = 0;
}


DotLight::DotLight() : BaseObject::BaseObject(), Id(700), Ia(700) { }
DotLight::DotLight(Dot3D<double> &in, double in_Id, double in_Ia)
{
    x = in.x;
    y = in.y;
    z = in.z;
    Id = in_Id;
    Ia = in_Ia;
}

DotLight::DotLight(const DotLight &in)
{
    (*this) = in;
}
DotLight::DotLight(DotLight &&in)
{
    (*this) = in;
    in.clear();
}
DotLight& DotLight::operator = (const DotLight& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    Id = in.Id;
    Ia = in.Ia;

    return (*this);
}
DotLight& DotLight::operator = (DotLight&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    Id = in.Id;
    Ia = in.Ia;

    in.clear();

    return *this;
}

void DotLight::clear()
{
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
    Id = 0;
    Ia = 0;
}

double DotLight::calcDiffuse(const Dot3D<double> &dot, const MathVector &norm) const
{
    MathVector light_beam(x-dot.x, y-dot.y, z-dot.z);

    double d = light_beam.len();
    light_beam.Ed();

    double cos_O = norm.scalarMult(light_beam);

    return Id*cos_O/(d+2000);
}
