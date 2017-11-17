#include "facade.h"

Facade::Facade()
{
    std::map<std::string, double> radius_koef = { {"mercury", 5.000},
                                                  {"venus", 9.600},
                                                  {"earth", 10.00},
                                                  {"mars", 8.000},
                                                  {"jupiter", 38.70},
                                                  {"saturn", 33.40},
                                                  {"uranus", 20.00},
                                                  {"neptune", 19.50},
                                                  {"sun", 218.0},
                                                  {"moon", 2.5} };

    std::map<std::string, double> distance_koef = { {"mercury", 0.387},
                                                    {"venus", 0.723},
                                                    {"earth", 1.000},
                                                    {"mars", 1.524},
                                                    {"jupiter", 3.004},
                                                    {"saturn", 5.252},
                                                    {"uranus", 7.19},
                                                    {"neptune", 9.07},
                                                    {"moon", 1.05} };

    std::map<std::string, double> ang_axis_to_orbit = { {"mercury", 7.00},
                                                        {"venus", 3.50},
                                                        {"earth", 23.5},
                                                        {"mars", 25.2},
                                                        {"jupiter", 3.00},
                                                        {"saturn", 26.7},
                                                        {"uranus", 82.0},
                                                        {"neptune", 29.0},
                                                        {"sun", 7.40},
                                                        {"moon", 1.54}};

    std::map<std::string, double> period_of_orbit_rotation = { {"mercury", 1/58.8},
                                                               {"venus", 1/243},
                                                               {"earth", 1},
                                                               {"mars", 1},
                                                               {"jupiter", 24/10},
                                                               {"saturn", 24/10},
                                                               {"uranus", 24/10},
                                                               {"neptune", 24/15},
                                                               {"sun", 1/24},
                                                               {"moon", 1/27}};

    std::map<std::string, double> sidereal_period = { {"mercury", 365/88},
                                                      {"venus", 365/225},
                                                      {"earth", 1},
                                                      {"mars", 1/1.88},
                                                      {"jupiter", 1/11.9},
                                                      {"saturn", 1/29.5},
                                                      {"uranus", 1/84.0},
                                                      {"neptune", 1/164},
                                                      {"moon", 10} };

    try
    {

        std::string path("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/textures");
        PlanetSystem* sys = nullptr;
        VisibleObject* pl = nullptr;
        double base_orbit_ang = solar_system.getOrbitBaseAng();
        double base_sun_ang = solar_system.getSunBaseAng();
        reader.openFile("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/new.obj");
        Obj sph = reader.read();
        reader.openFile("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/ring.obj");
        Obj rng = reader.read();
        Dot3D<double> pl_cent;


        ////////////////////////////// Солнце //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setObj(sph);
        pl->setKa(0.95);
        pl->setKd(0);
        pl->setZAng(ang_axis_to_orbit["sun"]);
        pl->setANG_PER_TICK_ROUND_SUN(0);
        pl->setANG_PER_TICK_ROUND_TURNCENT(0);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["sun"]*base_orbit_ang);
        pl->setScale(radius_koef["sun"]);
        pl->setTexture(path+std::string("/sun.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Солнце //////////////////////////////


        ////////////////////////////// Меркурий //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["mercury"]);
        pl->setZAng(ang_axis_to_orbit["mercury"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN*distance_koef["mercury"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["mercury"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["mercury"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["mercury"]*base_sun_ang);
        //pl->setX(2000);
        pl->setTexture(path+std::string("/mercury/mercury.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Меркурий //////////////////////////////



        ////////////////////////////// Венера //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["venus"]);
        pl->setZAng(ang_axis_to_orbit["venus"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["venus"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["venus"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["venus"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["venus"]*base_sun_ang);
        pl->setTexture(path+std::string("/venus/venus.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Венера //////////////////////////////


        ////////////////////////////// Земля //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["earth"]);
        pl->setZAng(ang_axis_to_orbit["earth"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["earth"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["earth"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["earth"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["earth"]*base_sun_ang);
        pl->setTexture(path+std::string("/earth/earth.jpg"));
        sys->add(pl);

        pl_cent = pl->getPosDot();

        // Луна
        pl = new Sphere;
        pl->setScale(radius_koef["moon"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["moon"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["earth"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["moon"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["moon"]*base_sun_ang);
        pl->setTexture(path+std::string("/earth/earth_moon.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Земля //////////////////////////////

        ////////////////////////////// Марс //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["mars"]);
        pl->setZAng(ang_axis_to_orbit["mars"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["mars"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["mars"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["mars"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["mars"]*base_sun_ang);
        pl->setTexture(path+std::string("/mars/mars.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Марс //////////////////////////////


        ////////////////////////////// Юпитер //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["jupiter"]);
        pl->setZAng(ang_axis_to_orbit["jupiter"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["jupiter"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["jupiter"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["jupiter"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["jupiter"]*base_sun_ang);
        pl->setTexture(path+std::string("/jupiter/jupiter.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Юпитер //////////////////////////////


        ////////////////////////////// Сатурн //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["saturn"]);
        pl->setZAng(ang_axis_to_orbit["saturn"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["saturn"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["saturn"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["saturn"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["saturn"]*base_sun_ang);
        pl->setTexture(path+std::string("/saturn/saturn.jpg"));
        sys->add(pl);

        // Кольца
        pl = new Ring;
        pl->setObj(rng);
        pl->setScale(radius_koef["saturn"]*1.3);
        pl->setZAng(ang_axis_to_orbit["saturn"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["saturn"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["saturn"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["saturn"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["saturn"]*base_sun_ang);
        pl->setTexture(path+std::string("/saturn/saturn_ring.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Сатурн //////////////////////////////


        ////////////////////////////// Уран //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["uranus"]);
        pl->setZAng(ang_axis_to_orbit["uranus"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["uranus"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["uranus"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["uranus"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["uranus"]*base_sun_ang);
        pl->setTexture(path+std::string("/uranus/uranus.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Уран //////////////////////////////


        ////////////////////////////// Нептун //////////////////////////////
        sys = new PlanetSystem;

        pl = new Sphere;
        pl->setScale(radius_koef["neptune"]);
        pl->setZAng(ang_axis_to_orbit["neptune"]);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["neptune"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["neptune"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["neptune"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["neptune"]*base_sun_ang);
        pl->setTexture(path+std::string("/neptune/neptune.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Нептун //////////////////////////////

        cam.setZ(-50000);

        light.setIa(255);
        light.setId(255);
    }
    catch(BaseErr&)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured while constructing Facade!");
        messageBox.setFixedSize(500,200);
    }


    /*
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setTexture(path+std::string("/sun.jpg"));
    sys->add(pl);

    pl = new Sphere;
    pl->setScale(0.5);
    pl->setX(200);
    pl->setTexture(path+std::string("/earth/earth.jpg"));
    sys->add(pl);

    solar_system.add(sys);

    cam.setZ(-250);
    */
}

Facade::Facade(const char *name)
{
    reader.openFile(name);
}

Facade::~Facade()
{
    solar_system.clear();
    reader.closeFile();
}

void Facade::camMove(GraphStruct &gr, InterfaceCommand *caps)
{
    if (caps)
    {
        caps->exec(cam);
    }
    draw(gr);
}

void Facade::planetMove(GraphStruct &gr)
{
    solar_system.tickMove();
    draw(gr);
}

void Facade::draw(GraphStruct &gr)
{
    Drawer dr;
    Transformer trans;
    gr.im.clrZBuf();
    gr.im.fill(Qt::black);
    VisibleObject* planet = nullptr;
    Dot3D<double> pl_cent;
    for (int i = 0; i < solar_system.size(); i++)
    {
        for (int j = 0; j < solar_system[i]->size(); j++)
        {
            planet = (*solar_system[i])[j];
            pl_cent = planet->getPosDot();

            Obj draw_object = planet->getTransformedObj();
            std::vector<double> I = planet->calcI(light);
            trans.proectToCam(draw_object, cam);
            trans.proectToCam(pl_cent, cam);
            if (pl_cent.z <= 0)
            {
                continue;
            }

            texture = planet->getTexture();

            Drwr::GraphicsToDraw gr_in(gr.im, cam, draw_object, texture, pl_cent, I, planet->isPlanet());
            dr.draw(gr_in);

            trans.clear();
        }
    }
}

void Facade::read(const char *name)
{
    reader.openFile(name);
    Obj tmp = reader.read();
    solar_system.setObj(tmp);
}
