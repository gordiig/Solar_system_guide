#include "transformer.h"

Transformer::Transformer()
{
    view_vector.setZ(-1);
    up_vector.setY(1);
    right_vector.setX(1);
}

Transformer::~Transformer()
{
    points.clear();
}

/**
 * @brief Transformer::move -- Перемещение в пр-ве
 * @param obj -- Объект переноса
 */
void Transformer::move(const Sphere &obj)
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x = obj[i].x + obj.x;
        points[i].y = obj[i].y + obj.y;
        points[i].z = obj[i].z + obj.z;
    }

    //return points;
}

/**
 * @brief Transformer::turn -- Поворот в пр-ве
 * @param obj -- Объект поворота
 */
void Transformer::turn(const Sphere &obj)
{
    double x_ang = obj.x_ang*M_PI/180;
    double y_ang = obj.y_ang*M_PI/180;
    double z_ang = obj.z_ang*M_PI/180;

    for (int i = 0; i < points.size(); i++)
    {
        double y_pr = points[i].y;
        points[i].y = obj.y + (y_pr-obj.y)*cos(x_ang) + (points[i].z-obj.z)*sin(x_ang);
        points[i].z = obj.z - (y_pr-obj.y)*sin(x_ang) + (points[i].z-obj.z)*cos(x_ang);

        double x_pr = points[i].x;
        points[i].x = obj.x + (x_pr-obj.x)*cos(y_ang) - (points[i].z-obj.z)*sin(y_ang);
        points[i].z = obj.z + (x_pr-obj.x)*sin(y_ang) + (points[i].z-obj.z)*cos(y_ang);

        x_pr = points[i].x;
        points[i].x = obj.x + (x_pr-obj.x)*cos(z_ang) - (points[i].y-obj.y)*sin(z_ang);
        points[i].y = obj.y + (x_pr-obj.x)*sin(z_ang) + (points[i].y-obj.y)*cos(z_ang);
    }
}

void Transformer::turn(const Camera &cam)
{
    double x_ang = cam.getXAng() * M_PI/180;
    double y_ang = cam.getYAng() * M_PI/180;
    double z_ang = cam.getZAng() * M_PI/180;

    // По Ох
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(x_ang) + up_vector.getZ()*sin(x_ang));
    up_vector.setZ(-y_pr*sin(x_ang) + up_vector.getZ()*cos(x_ang));
    y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(x_ang) + view_vector.getZ()*sin(x_ang));
    view_vector.setZ(-y_pr*sin(x_ang) + view_vector.getZ()*cos(x_ang));
    y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(x_ang) + right_vector.getZ()*sin(x_ang));
    right_vector.setZ(-y_pr*sin(x_ang) + right_vector.getZ()*cos(x_ang));

    // По Оу
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(y_ang) - right_vector.getZ()*sin(y_ang));
    right_vector.setZ(x_pr*sin(y_ang) + right_vector.getZ()*cos(y_ang));
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(y_ang) - view_vector.getZ()*sin(y_ang));
    view_vector.setZ(x_pr*sin(y_ang) + view_vector.getZ()*cos(y_ang));
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(y_ang) - up_vector.getZ()*sin(y_ang));
    up_vector.setZ(x_pr*sin(y_ang) + up_vector.getZ()*cos(y_ang));

    // По Оz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(z_ang) - right_vector.getY()*sin(z_ang));
    right_vector.setY(x_pr*sin(z_ang) + right_vector.getY()*cos(z_ang));
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(z_ang) - up_vector.getY()*sin(z_ang));
    up_vector.setY(x_pr*sin(z_ang) + up_vector.getY()*cos(z_ang));
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(z_ang) - view_vector.getY()*sin(z_ang));
    view_vector.setY(x_pr*sin(z_ang) + view_vector.getY()*cos(z_ang));
}

void Transformer::proectToCam(const Camera& cam)
{
    for (int i = 0; i < points.size(); i++)
    {
        double x = points[i].x;
        double y = points[i].y;
        double z = points[i].z;

        points[i].x = x*right_vector.getX() + y*right_vector.getY() + z*right_vector.getZ() - cam.getX();
        points[i].y = x*up_vector.getX() + y*up_vector.getY() + z*up_vector.getZ() - cam.getY();
        points[i].z = x*view_vector.getX() + y*view_vector.getY() + z*view_vector.getZ() - cam.getZ();

        points[i].x *= (cam.getDistanceToScreen() / points[i].z);
        points[i].y *= (cam.getDistanceToScreen() / points[i].z);
    }
}

/**
 * @brief Transformer::transform -- Функция трансформации точек для вывода на экран
 * @param obj -- Трансформирующийся объект
 * @return Массив преобразованных точек
 */
Points3D& Transformer::transform(const Sphere &obj, const Camera &cam)
{
    points = obj.obj.getPoints();

    move(obj);
    turn(obj);
    turn(cam);
    proectToCam(cam);

    return points;
}

Dot3D<double> Transformer::transform(const DotLight &light, const Camera &cam)
{
    Dot3D<double> ans;

    double x = light.getX();
    double y = light.getY();
    double z = light.getZ();

    ans.x = x*right_vector.getX() + y*right_vector.getX() + z*right_vector.getZ() - cam.getX();
    ans.y = x*up_vector.getX() + y*up_vector.getX() + z*up_vector.getZ() - cam.getY();
    ans.z = x*view_vector.getX() + y*view_vector.getX() + z*view_vector.getZ() - cam.getZ();

    //ans.x *= (cam.getDistanceToScreen() / ans.z);
    //ans.y *= (cam.getDistanceToScreen() / ans.z);

    return ans;
}
