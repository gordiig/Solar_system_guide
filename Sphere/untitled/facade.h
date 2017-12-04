#ifndef FACADE_H
#define FACADE_H

#include <thread>
#include <map>
#include <QMessageBox>

#include "errors.h"
#include "obj.h"
#include "reader.h"
#include "comcapsule.h"
#include "mydisplay.h"
#include "spacesystems.h"

#include "transformer.h"
#include "drawer.h"

struct GraphStruct
{
    MyDisplay &im;

    GraphStruct(MyDisplay& in) : im(in) {}
};

enum CamForPlanet
{
    sun_cam = 0,
    mercury_cam,
    venus_cam,
    earth_cam,
    mars_cam,
    jupiter_cam,
    saturn_cam,
    uranus_cam,
    neptune_cam,
};

enum ModelSize
{
    normal = 0,
    medium,
    bad,
};

class Facade
{
private:
    SolarSystem solar_system;
    QImage* texture;
    Reader reader;
    DotLight light;
    Camera* cam;
    Drawer dr;

    bool change_painter;
    int prev_painter;

    const double EARTH_DISTANCE_FROM_SUN = 90000;
    const double CAMERA_DISTANCE = 1353494.5;

    Facade(const Facade&);
    Facade(Facade&&);
    Facade& operator = (const Facade&);

public:
    Facade();
    Facade(const char *name);
    ~Facade();

    void camMove(GraphStruct& gr, InterfaceCommand *caps = nullptr);
    void planetMove(GraphStruct& gr);

    void draw(GraphStruct &gr);
    void read(const char *name = "new.obj");

    void camChange(int cam_num);
    void painterChange();
    void modelChange(int size);
};

#endif // FACADE_H
