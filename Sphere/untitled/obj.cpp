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
    texture_coord = in.texture_coord;
    poly = in.poly;

    return *this;
}
Obj& Obj::operator = (Obj&& in)
{
    clear();

    points = in.points;
    texture_coord = in.texture_coord;
    poly = in.poly;

    in.clear();

    return *this;
}

Obj::Obj(const Points3D &in_1, const Points2D &in_2, const PolyList &in_3)
{
    points = in_1;
    texture_coord = in_2;
    poly = in_3;
}
Obj::Obj(Points3D &&in_1, Points2D &&in_2, PolyList &&in_3)
{
    points = in_1;
    texture_coord = in_2;
    poly = in_3;

    in_1.clear();
    in_2.clear();
    for (auto &x : in_3)
    {
        x.clear();
    }
    in_3.clear();
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
Points2D Obj::makeTexCut(int i) const
{
    Points2D ans;
    for (auto &x : poly[i])
    {
        ans.push_back(texture_coord[x-1]);
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



Camera::Camera(int in_id) : BaseObject::BaseObject()
{
    view_axis.setZ(1);
    right_axis.setX(1);
    up_axis.setY(1);
    distance_to_screen = 500;
    z = -700;
    id = in_id;

}
Camera::Camera(double in_x, double in_y, double in_z, int in_id) :
    BaseObject::BaseObject(in_x, in_y, in_z)
{
    view_axis.setZ(1);
    right_axis.setX(1);
    up_axis.setY(1);
    distance_to_screen = 500;
    id = in_id;
}
Camera::Camera(Dot3D<double> in_dot, double in_x_ang, double in_y_ang, double in_z_ang, int in_id)
{
    x = in_dot.x;
    y = in_dot.y;
    z = in_dot.z;

    x_ang = in_x_ang;
    y_ang = in_y_ang;
    z_ang = in_z_ang;

    view_axis.setZ(1);
    right_axis.setX(1);
    up_axis.setY(1);
    distance_to_screen = 500;
    id = in_id;
}

Camera::Camera(const Camera &in)
{
    (*this) = in;
}
Camera::Camera(Camera &&in)
{
    (*this) = in;
    in.clear();
}
Camera& Camera::operator = (const Camera& in)
{
    view_axis = in.view_axis;
    right_axis = in.right_axis;
    up_axis = in.up_axis;
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    id = in.id;

    return (*this);
}
Camera& Camera::operator = (Camera&& in)
{
    view_axis = in.view_axis;
    right_axis = in.right_axis;
    up_axis = in.up_axis;
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    id = in.id;

    in.clear();
    return (*this);
}

double Camera::getRightAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ох
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getX();
}
double Camera::getRightAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ox
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));


    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getY();
}
double Camera::getRightAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ox
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getZ();
}
MathVector Camera::getRightAxis() const
{
    return MathVector(getRightAxisX(), getRightAxisY(), getRightAxisZ());
}

double Camera::getUpAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getX();
}
double Camera::getUpAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getY();
}
double Camera::getUpAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getZ();
}
MathVector Camera::getUpAxis() const
{
    return MathVector(getUpAxisX(), getUpAxisY(), getUpAxisZ());
}

double Camera::getViewAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getX();
}
double Camera::getViewAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getY();
}
double Camera::getViewAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getZ();
}
MathVector Camera::getViewAxis() const
{
    return MathVector(getViewAxisX(), getViewAxisY(), getViewAxisZ());
}

void Camera::moveToWorldCenter()
{
    clear();
    view_axis.setZ(1);
    up_axis.setY(1);
    right_axis.setX(1);
}
void Camera::clear()
{
    view_axis.clear();
    up_axis.clear();
    right_axis.clear();
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
}

bool Camera::isPolyViz(const Points3D &points) const
{
    return true;
}
bool Camera::isPolyViz(const Points3D &points, Dot3D<double> &cent_dot, bool is_planet) const
{
    if (!is_planet) return true;

    if (points.size() < 3)
    {
        throw NotEnoughPointsForPoly("\nIn file \"Camera.cpp\" in Camera::IsPolyVis()\n");
    }

    int num = 0;
    double min_z = points[0].z;
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].z < min_z)
        {
            num = i;
            min_z = points[i].z;
        }
    }

    MathVector poly_norm(points[num].x-cent_dot.x, points[num].y-cent_dot.y, points[num].z-cent_dot.z);
    MathVector cam_vector(points[num].x, points[num].y, points[num].z);

    return (poly_norm.scalarMult(cam_vector) > 0) ? (false) : (true);
}
bool Camera::isOnDisplay(const DotForDrawer &point) const
{
    return isOnDisplay(point.z);
}
bool Camera::isOnDisplay(const double z) const
{
    return (z > distance_to_screen) ? true : false;
}

void Camera::lineCut(Line<double> &line) const
{
    if ((line.beg.z < distance_to_screen) && (line.end.z < distance_to_screen))
    {
        line.beg = Dot3D<double>(-1, -1, -1);
        return;
    }

    if (line.beg.z < distance_to_screen)
    {
        double t = (distance_to_screen - line.beg.z) / (line.end.z - line.beg.z);
        line.beg.z = distance_to_screen;
        line.beg.x = line.beg.x + t*(line.end.x - line.beg.x);
        line.beg.y = line.beg.y + t*(line.end.y - line.beg.y);
        return;
//        line.beg = Dot3D<double>(-1, -1, -1);
//        return;
    }

    if (line.end.z < distance_to_screen)
    {
        double t = (distance_to_screen - line.beg.z) / (line.end.z - line.beg.z);
        line.end.z = distance_to_screen;
        line.end.x = line.beg.x + t*(line.end.x - line.beg.x);
        line.end.y = line.beg.y + t*(line.end.y - line.beg.y);
        return;
//        line.beg = Dot3D<double>(-1, -1, -1);
//        return;
    }
}


Obj Sphere::obj;
Obj Sphere::transformed_obj;

Sphere::Sphere() : VisibleObject::VisibleObject(), texture(nullptr),
    ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr){ }
Sphere::Sphere(const double in_x, const double in_y, const double in_z) :
    VisibleObject::VisibleObject(in_x, in_y, in_z), texture(nullptr),
    ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr) { }
Sphere::Sphere(const double in_x, const double in_y, const double in_z,
               const double in_x_ang, const double in_y_ang, const double in_z_ang) :
    VisibleObject::VisibleObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang),
    texture(nullptr), ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr) { }
Sphere::Sphere(const double in_x, const double in_y, const double in_z,
               const double in_x_ang, const double in_y_ang, const double in_z_ang,
               const int in_kd, const int in_ka) :
    VisibleObject::VisibleObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang, in_kd, in_ka),
    texture(nullptr), ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr){ }
Sphere::Sphere(Dot3D<double> &in) : VisibleObject::VisibleObject(in), texture(nullptr),
    ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr) { }
Sphere::Sphere(Dot3D<int> &in) : VisibleObject::VisibleObject(in), texture(nullptr),
    ANG_PER_TICK_ROUND_SUN(1), ANG_PER_TICK_ROUND_ORBITE(1), cam(nullptr) { }

Sphere::Sphere(const Points3D &in_points, const Points2D &in_tex, const PolyList &in_poly)
{
    Obj tmp(in_points, in_tex, in_poly);
    obj = tmp;
    texture = nullptr;
    cam = nullptr;
}
Sphere::Sphere(Points3D &&in_points, Points2D &&in_tex, PolyList &&in_poly)
{
    Obj tmp(in_points, in_tex, in_poly);
    obj = tmp;
    texture = nullptr;
    cam = nullptr;

    in_points.clear();
    in_tex.clear();
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
    texture_path = in.texture_path;
    texture = in.texture;

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
    texture = in.texture;
    texture_path = in.texture_path;

    in.clear();

    return (*this);
}

Sphere::~Sphere()
{
    clear();
}

void Sphere::initCam()
{
    cam = new Camera(x, y - getRadius()*0.8, z - getRadius()*CONST_FOR_CAMERA, Camera::fixed_cam);
}

Dot3D<double>& Sphere::operator [] (int i) const
{
    return obj.points[i];
}

MathVector Sphere::getPointNorm(int pt_n) const
{
    if (pt_n >= obj.points.size())
    {
        throw VecRangeErr("From getPointNorm() in obj.cpp");
    }

    return MathVector(transformed_obj.points[pt_n].x-x, transformed_obj.points[pt_n].y-y, transformed_obj.points[pt_n].z-z);
}
std::vector<MathVector> Sphere::getAllNorm() const
{
    std::vector<MathVector> ans;
    for (int i = 0; i < obj.points.size(); i++)
    {
        ans.push_back(MathVector(obj.points[i].x-x, obj.points[i].y-y, obj.points[i].z-z));
    }

    return ans;
}
Camera* Sphere::getCam()
{
    if (!cam)
    {
        initCam();
    }

    return cam;
}

void Sphere::setTexture(const std::string &path)
{
    setTexture(path.c_str());
}
void Sphere::setTexture(const char *path)
{
    if (texture)
    {
        delete texture;
    }

    texture = new QImage(QString(path));
    if (texture->isNull())
    {
        setTexture("../../../../Contents/textures/testcat.jpg");
        //throw ImgOpenErr("Sphere::setTexture() from obj.cpp\n");
    }

    texture_path = path;
}
void Sphere::setTexture(QImage *image)
{
    if (texture)
    {
        delete texture;
    }

    texture = image;
}

Points3D Sphere::getScaledPoints() const
{
    Points3D ans;

    for (auto &x : obj.points)
    {
        ans.push_back(Dot3D<double>(x.x*scale, x.y*scale, x.z*scale));
    }

    return ans;
}
double Sphere::getRadius() const
{
//    return sqrt(SQR(transformed_obj.points[0].x - x) + SQR(transformed_obj.points[0].y - y)
//            + SQR(transformed_obj.points[0].z - z));
    return 100*scale;
}

void Sphere::transform()
{
    transformed_obj = obj;
    resize();
    move();
    turn();
}
void Sphere::resize()
{
    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        transformed_obj.points[i].x *= scale;
        transformed_obj.points[i].y *= scale;
        transformed_obj.points[i].z *= scale;
    }
}
void Sphere::turn()
{
    double _x_ang = x_ang*M_PI/180;
    double _y_ang = y_ang*M_PI/180;
    double _z_ang = z_ang*M_PI/180;

    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        double y_pr = transformed_obj.points[i].y;
        transformed_obj.points[i].y = y + (y_pr-y)*cos(_x_ang) + (transformed_obj.points[i].z-z)*sin(_x_ang);
        transformed_obj.points[i].z = z - (y_pr-y)*sin(_x_ang) + (transformed_obj.points[i].z-z)*cos(_x_ang);

        double x_pr = transformed_obj.points[i].x;
        transformed_obj.points[i].x = x + (x_pr-x)*cos(_y_ang) - (transformed_obj.points[i].z-z)*sin(_y_ang);
        transformed_obj.points[i].z = z + (x_pr-x)*sin(_y_ang) + (transformed_obj.points[i].z-z)*cos(_y_ang);

        x_pr = transformed_obj.points[i].x;
        transformed_obj.points[i].x = x + (x_pr-x)*cos(_z_ang) - (transformed_obj.points[i].y-y)*sin(_z_ang);
        transformed_obj.points[i].y = y + (x_pr-x)*sin(_z_ang) + (transformed_obj.points[i].y-y)*cos(_z_ang);
    }
}
void Sphere::move()
{
    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        transformed_obj.points[i].x += x;
        transformed_obj.points[i].y += y;
        transformed_obj.points[i].z += z;
    }
}

std::vector<double> Sphere::calcI(const DotLight &light) const
{
    std::vector<double> ans;
    Points3D& points = transformed_obj.points;

    for (int i = 0; i < points.size(); i++)
    {
        MathVector norm = getPointNorm(i);
        double I = light.getIa()*ka + light.calcDiffuse(points[i], norm.getEd())*kd;
        ans.push_back(I);
    }

    return ans;
}

void Sphere::recalcCamPos()
{
    if (cam)
    {
        cam->setX(x);
        cam->setY(y - getRadius()*0.8);
        cam->setZ(z - getRadius()*CONST_FOR_CAMERA);
    }
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
    texture_path.clear();
    if (texture)
    {
        delete texture;
    }
    if (cam)
    {
        delete cam;
    }
}



Obj Ring::obj;
Obj Ring::transformed_obj;
Ring::Ring() : VisibleObject::VisibleObject(), texture(nullptr) {}

Ring::Ring(const Points3D &in_points, const Points2D &in_tex, const PolyList &in_poly)
{
    Obj tmp(in_points, in_tex, in_poly);
    obj = tmp;
    texture = nullptr;
}
Ring::Ring(Points3D &&in_points, Points2D &&in_tex, PolyList &&in_poly)
{
    Obj tmp(in_points, in_tex, in_poly);
    obj = tmp;
    texture = nullptr;

    in_points.clear();
    in_tex.clear();
    for (auto &x : in_poly)
    {
        x.clear();
    }
    in_poly.clear();
}

Ring::Ring(const Ring &in)
{
    *this = in;
}
Ring::Ring(Ring &&in)
{
    *this = in;
    in.clear();
}

Ring::~Ring()
{
    clear();
}

Ring& Ring::operator = (const Ring& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;
    texture_path = in.texture_path;
    texture = in.texture;

    return (*this);
}
Ring& Ring::operator = (Ring&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;
    texture = in.texture;
    texture_path = in.texture_path;

    in.clear();

    return (*this);
}

Dot3D<double>& Ring::operator [] (int i) const
{
    return obj.points[i];
}

MathVector Ring::getPointNorm(int pt_n) const
{
    if (pt_n >= obj.points.size())
    {
        throw VecRangeErr("From getPointNorm() in obj.cpp");
    }

    MathVector norm(0, -1, 0);
    if (pt_n < obj.points.size()/2)
    {
        norm.setY(1);
    }

    double _x_ang = x_ang*M_PI/180;
    double _y_ang = y_ang*M_PI/180;
    double _z_ang = z_ang*M_PI/180;

    double y_pr = norm.getY();
    norm.setY(y + (y_pr-y)*cos(_x_ang) + (norm.getZ()-z)*sin(_x_ang));
    norm.setZ(z - (y_pr-y)*sin(_x_ang) + (norm.getZ()-z)*cos(_x_ang));

    double x_pr = norm.getX();
    norm.setX(x + (x_pr-x)*cos(_y_ang) - (norm.getZ()-z)*sin(_y_ang));
    norm.setZ(z + (x_pr-x)*sin(_y_ang) + (norm.getZ()-z)*cos(_y_ang));

    x_pr = norm.getX();
    norm.setX(x + (x_pr-x)*cos(_z_ang) - (norm.getY()-y)*sin(_z_ang));
    norm.setY(y + (x_pr-x)*sin(_z_ang) + (norm.getY()-y)*cos(_z_ang));

    return norm;
}
std::vector<MathVector> Ring::getAllNorm() const
{
    std::vector<MathVector> ans;
    for (int i = 0; i < obj.points.size(); i++)
    {
        ans.push_back(getPointNorm(i));
    }

    return ans;
}

void Ring::setTexture(const std::string &path)
{
    setTexture(path.c_str());
}
void Ring::setTexture(const char *path)
{
    if (texture)
    {
        delete texture;
    }

    texture = new QImage(QString(path));
    if (texture->isNull())
    {
        setTexture("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/"
                   "Sphere/Contents/textures/testcat.jpg");
        //throw ImgOpenErr("Sphere::setTexture() from obj.cpp\n");
    }

    texture_path = path;
}
void Ring::setTexture(QImage *image)
{
    if (texture)
    {
        delete texture;
    }

    texture = image;
}

Points3D Ring::getScaledPoints() const
{
    Points3D ans;

    for (auto &x : obj.points)
    {
        ans.push_back(Dot3D<double>(x.x*scale, x.y*scale, x.z*scale));
    }

    return ans;
}

void Ring::transform()
{
    transformed_obj = obj;
    resize();
    move();
    turn();
}
void Ring::resize()
{
    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        transformed_obj.points[i].x *= scale;
        transformed_obj.points[i].y *= scale;
        transformed_obj.points[i].z *= scale;
    }
}
void Ring::turn()
{
    double _x_ang = x_ang*M_PI/180;
    double _y_ang = y_ang*M_PI/180;
    double _z_ang = z_ang*M_PI/180;

    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        double y_pr = transformed_obj.points[i].y;
        transformed_obj.points[i].y = y + (y_pr-y)*cos(_x_ang) + (transformed_obj.points[i].z-z)*sin(_x_ang);
        transformed_obj.points[i].z = z - (y_pr-y)*sin(_x_ang) + (transformed_obj.points[i].z-z)*cos(_x_ang);

        double x_pr = transformed_obj.points[i].x;
        transformed_obj.points[i].x = x + (x_pr-x)*cos(_y_ang) - (transformed_obj.points[i].z-z)*sin(_y_ang);
        transformed_obj.points[i].z = z + (x_pr-x)*sin(_y_ang) + (transformed_obj.points[i].z-z)*cos(_y_ang);

        x_pr = transformed_obj.points[i].x;
        transformed_obj.points[i].x = x + (x_pr-x)*cos(_z_ang) - (transformed_obj.points[i].y-y)*sin(_z_ang);
        transformed_obj.points[i].y = y + (x_pr-x)*sin(_z_ang) + (transformed_obj.points[i].y-y)*cos(_z_ang);
    }
}
void Ring::move()
{
    for (int i = 0; i < transformed_obj.points.size(); i++)
    {
        transformed_obj.points[i].x += x;
        transformed_obj.points[i].y += y;
        transformed_obj.points[i].z += z;
    }
}

std::vector<double> Ring::calcI(const DotLight &light) const
{
    std::vector<double> ans;
    Points3D points = transformed_obj.points;
    double I = 0;

    for (int i = 0; i < points.size(); i++)
    {
        MathVector norm = getPointNorm(i);

        I = light.getIa()*ka + light.calcDiffuse(points[i], norm.getEd())*kd;
        ans.push_back(I);
    }

    return ans;
}

void Ring::clear()
{
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
    ka = 0;
    kd = 0;
    texture_path.clear();
    if (texture)
    {
        delete texture;
    }
}


DotLight::DotLight() : BaseObject::BaseObject(), Id(250), Ia(250) { }
DotLight::DotLight(Dot3D<double> &in, double in_Id, double in_Ia)
{
    x = in.x;
    y = in.y;
    z = in.z;
    Id = in_Id;
    Ia = in_Ia;
}
DotLight::DotLight(Dot3D<double> &&in, double in_Id, double in_Ia)
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

std::vector<double> DotLight::calcI(const Obj &planet, const Dot3D<double>& c_d,
                                    double ka, double kd)
{
    std::vector<double> ans;
    Points3D points = planet.getPoints();
    double I = 0;

    for (int i = 0; i < points.size(); i++)
    {
        MathVector norm(points[i].x - c_d.x, points[i].y - c_d.y, points[i].z - c_d.z);
        I = Ia*ka + calcDiffuse(points[i], norm.getEd())*kd;
        ans.push_back(I);
    }

    return ans;
}

double DotLight::calcDiffuse(const Dot3D<double> &dot, const MathVector &norm) const
{
    MathVector light_beam(x-dot.x, y-dot.y, z-dot.z);

    double d = light_beam.len();
    light_beam.Ed();

    //MathVector norm2 = norm;
    //norm2.invert();

    double cos_O = norm.scalarMult(light_beam);
    if (cos_O <= 0)
    {
        return 0;
    }

    return Id*cos_O/(1);
}
