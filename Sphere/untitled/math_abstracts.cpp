#include "math_abstracts.h"

//using namespace MathFunctions;


MathVector::MathVector() : BaseObject::BaseObject() { }
MathVector::MathVector(double in_x, double in_y, double in_z) :
    BaseObject::BaseObject(in_x, in_y, in_z) { }
MathVector::MathVector(double in_x, double in_y, double in_z,
                       double in_x_ang, double in_y_ang, double in_z_ang) :
    BaseObject::BaseObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang) { }
MathVector::MathVector(const Dot3D<double> &in) : BaseObject::BaseObject(in) { }
MathVector::MathVector(const Dot3D<double> &in_1, const Dot3D<double> &in_2) :
    BaseObject(in_2.x - in_1.x, in_2.y - in_1.y, in_2.z - in_1.z) { }

MathVector::MathVector(const MathVector &in)
{
    (*this) = in;
}
MathVector::MathVector(MathVector &&in)
{
    (*this) = in;

    in.clear();
}
MathVector& MathVector::operator = (const MathVector& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    return (*this);
}
MathVector& MathVector::operator = (MathVector&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    in.clear();
    return (*this);
}

double MathVector::len() const
{
    return sqrt(x*x + y*y + z*z);
}
double MathVector::scalarMult(const MathVector &in) const
{
    return x*in.x + y*in.y + z*in.z;
}

MathVector& MathVector::invert()
{
    x = -x;
    y = -y;
    z = -z;

    return (*this);
}
MathVector MathVector::getInvert() const
{
    MathVector ans(*this);
    return ans.invert();
}
MathVector& MathVector::Ed()
{
    double l = this->len();

    x /= l;
    y /= l;
    z /= l;

    return (*this);
}
MathVector MathVector::getEd() const
{
    MathVector ans(*this);
    return ans.Ed();
}
