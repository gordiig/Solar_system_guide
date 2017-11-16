#include "facade.h"

Facade::Facade()
{
    std::map<char, double> radius_koef = {{'m', 5.000},
                                          {'v', 9.600},
                                          {'e', 10.00},
                                          {'M', 8.000},
                                          {'j', 38.70},
                                          {'s', 33.40},
                                          {'u', 20.00},
                                          {'n', 19.50},
                                          {'S', 218.0}};

    std::map<char, double> distance_koef = {{'m', 0.387},
                                            {'v', 0.723},
                                            {'e', 1.000},
                                            {'M', 1.524},
                                            {'j', 3.004},
                                            {'s', 5.252},
                                            {'u', 7.19},
                                            {'n', 9.07}};

    std::map<char, double> ang_axis_to_orbit = {{'m', 7.00},
                                                {'v', 3.50},
                                                {'e', 23.5},
                                                {'M', 25.2},
                                                {'j', 3.00},
                                                {'s', 26.7},
                                                {'u', 82.0},
                                                {'n', 29.0},
                                                {'S', 7.40}};

    std::map<char, double> period_of_orbit_rotation = {{'m', 1/58.8},
                                                       {'v', 1/243},
                                                       {'e', 1},
                                                       {'M', 1},
                                                       {'j', 24/10},
                                                       {'s', 24/10},
                                                       {'u', 24/10},
                                                       {'n', 24/15},
                                                       {'S', 1/24}};

    std::map<char, double> sidereal_period = {{'m', 365/88},
                                              {'v', 365/225},
                                              {'e', 1},
                                              {'M', 1/1.88},
                                              {'j', 1/11.9},
                                              {'s', 1/29.5},
                                              {'u', 1/84.0},
                                              {'n', 1/164}};

    std::string path("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/textures");
    PlanetSystem* sys = nullptr;
    VisibleObject* pl = nullptr;
    double base_orbit_ang = solar_system.getOrbitBaseAng();
    double base_sun_ang = solar_system.getSunBaseAng();
    reader.openFile("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/new.obj");
    Obj sph = reader.read();
    reader.openFile("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/ring.obj");
    Obj rng = reader.read();



    ////////////////////////////// Солнце //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setObj(sph);
    pl->setKa(0.95);
    pl->setKd(0);
    pl->setZAng(ang_axis_to_orbit['S']);
    pl->setANG_PER_TICK_ROUND_SUN(0);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['S']*base_orbit_ang);
    pl->setScale(radius_koef['S']);
    pl->setTexture(path+std::string("/sun.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Солнце //////////////////////////////


    ////////////////////////////// Меркурий //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['m']);
    pl->setZAng(ang_axis_to_orbit['m']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN*distance_koef['m']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['m']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['m']*base_orbit_ang);
    //pl->setX(2000);
    pl->setTexture(path+std::string("/mercury/mercury.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Меркурий //////////////////////////////



    ////////////////////////////// Венера //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['v']);
    pl->setZAng(ang_axis_to_orbit['v']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['v']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['v']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['v']*base_orbit_ang);
    pl->setTexture(path+std::string("/venus/venus.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Венера //////////////////////////////


    ////////////////////////////// Земля //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['e']);
    pl->setZAng(ang_axis_to_orbit['e']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['e']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['e']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['e']*base_orbit_ang);
    pl->setTexture(path+std::string("/earth/earth.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Земля //////////////////////////////

    ////////////////////////////// Марс //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['M']);
    pl->setZAng(ang_axis_to_orbit['M']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['M']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['M']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['M']*base_orbit_ang);
    pl->setTexture(path+std::string("/mars/mars.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Марс //////////////////////////////


    ////////////////////////////// Юпитер //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['j']);
    pl->setZAng(ang_axis_to_orbit['j']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['j']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['j']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['j']*base_orbit_ang);
    pl->setTexture(path+std::string("/jupiter/jupiter.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Юпитер //////////////////////////////


    ////////////////////////////// Сатурн //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['s']);
    pl->setZAng(ang_axis_to_orbit['s']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['s']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['s']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['s']*base_orbit_ang);
    pl->setTexture(path+std::string("/saturn/saturn.jpg"));
    sys->add(pl);

    pl = new Ring;
    pl->setObj(rng);
    pl->setScale(radius_koef['s']*1.3);
    pl->setZAng(ang_axis_to_orbit['s']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['s']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['s']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['s']*base_orbit_ang);
    pl->setTexture(path+std::string("/testcat.jpg"));
    sys->add(pl);


    solar_system.add(sys);
    ////////////////////////////// !Сатурн //////////////////////////////


    ////////////////////////////// Уран //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['u']);
    pl->setZAng(ang_axis_to_orbit['u']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['u']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['u']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['u']*base_orbit_ang);
    pl->setTexture(path+std::string("/uranus/uranus.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Уран //////////////////////////////


    ////////////////////////////// Нептун //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['n']);
    pl->setZAng(ang_axis_to_orbit['n']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['n']);
    pl->setANG_PER_TICK_ROUND_SUN(sidereal_period['n']*base_sun_ang);
    pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation['n']*base_orbit_ang);
    pl->setTexture(path+std::string("/neptune/neptune.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Нептун //////////////////////////////

    cam.setZ(-50000);

    light.setIa(255);
    light.setId(255);


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
            std::vector<double> I = planet->calcI(light);/*light.calcI(draw_object, pl_cent, planet->getKa(), planet->getKd())*/;
            trans.proectToCam(draw_object, cam);
            trans.proectToCam(pl_cent, cam);
            if (pl_cent.z <= 0)
            {
                continue;
            }

            //DotLight draw_light(trans.transform(light, cam), 255, 255);

            texture = planet->getTexture();

            Drwr::GraphicsToDraw gr_in(gr.im, cam, draw_object, texture, pl_cent, I);
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
