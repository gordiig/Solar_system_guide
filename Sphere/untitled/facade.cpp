#include "facade.h"

Facade::Facade()
{
    tot_time = 0;
    cnt = 0;

    std::map<std::string, double> radius_koef = { {"mercury", 5.000},
                                                  {"venus", 9.600},
                                                  {"earth", 10.00},
                                                  {"mars", 8.000},
                                                  {"jupiter", 38.70},
                                                  {"saturn", 33.40},
                                                  {"uranus", 20.00},
                                                  {"neptune", 19.50},
                                                  {"sun", 218.0},
                                                  {"moon", 2.5},
                                                  {"phobos", 1.1},
                                                  {"deimos", 0.7},
                                                  {"ganimed", 7.},
                                                  {"calisto", 4.},
                                                  {"titan", 5.},
                                                  {"japet", 2.},
                                                  {"titania", 5.},
                                                  {"oberon", 2.},
                                                  {"triton", 4.},
                                                  {"protei", 3.} };

    distance_koef = { {"mercury", 0.587},
                      {"venus", 0.723},
                      {"earth", 1.000},
                      {"mars", 1.524},
                      {"jupiter", 3.004},
                      {"saturn", 5.252},
                      {"uranus", 7.19},
                      {"neptune", 9.07},
                      {"moon", 1.05},
                      {"phobos", 1.574},
                      {"deimos", 1.599},
                      {"ganimed", 3.150},
                      {"calisto", 3.29},
                      {"titan", 5.352},
                      {"japet", 5.402},
                      {"titania", 7.27},
                      {"oberon", 7.31},
                      {"triton", 9.24},
                      {"protei", 9.37} };

    std::map<std::string, double> ang_axis_to_orbit = { {"mercury", 7.00},
                                                        {"venus", 3.50},
                                                        {"earth", 23.5},
                                                        {"mars", 25.2},
                                                        {"jupiter", 3.00},
                                                        {"saturn", 26.7},
                                                        {"uranus", 82.0},
                                                        {"neptune", 29.0},
                                                        {"sun", 7.40},
                                                        {"moon", 1.54},
                                                        {"phobos", 0},
                                                        {"deimos", 30},
                                                        {"ganimed", 20.},
                                                        {"calisto", 17.},
                                                        {"titan", 5.},
                                                        {"japet", 2.},
                                                        {"titania", 5.},
                                                        {"oberon", 2.},
                                                        {"triton", 6.},
                                                        {"protei", 1.} };

    std::map<std::string, double> period_of_orbit_rotation = { {"mercury", 1/15.},
                                                               {"venus", -1/10.},
                                                               {"earth", 1},
                                                               {"mars", 1},
                                                               {"jupiter", 24/10.},
                                                               {"saturn", 24/10.},
                                                               {"uranus", 24/10.},
                                                               {"neptune", 24/15.},
                                                               {"sun", 1/24.},
                                                               {"moon", 1/27.},
                                                               {"phobos", 1},
                                                               {"deimos", 1},
                                                               {"ganimed", 2},
                                                               {"calisto", 5},
                                                               {"titan", 5.},
                                                               {"japet", 2.},
                                                               {"titania", 3.},
                                                               {"oberon", 2.},
                                                               {"triton", 6.},
                                                               {"protei", 1.} };

    std::map<std::string, double> sidereal_period = { {"mercury", 365/88.},
                                                      {"venus", 365/225.},
                                                      {"earth", 1},
                                                      {"mars", 1/1.88},
                                                      {"jupiter", 1/11.9},
                                                      {"saturn", 1/29.5},
                                                      {"uranus", 1/84.0},
                                                      {"neptune", 1/164.},
                                                      {"moon", 4},
                                                      {"phobos", 5},
                                                      {"deimos", 3},
                                                      {"ganimed", 5},
                                                      {"calisto", 3},
                                                      {"titan", 5.},
                                                      {"japet", 2.},
                                                      {"titania", 3.},
                                                      {"oberon", 1.},
                                                      {"triton", 6.},
                                                      {"protei", 1.8} };

    int orb_sections = 50;
    double x = 100, z = 0;
    double alpha = 2*M_PI/orb_sections;
    for (int i = 0; i < orb_sections; i++)
    {
        double x_in = x*cos(alpha*i) - z*sin(alpha*i);
        double z_in = z*cos(alpha*i) + x*sin(alpha*i);
        orbite.push_back(Dot3D<double>(x_in, 0, z_in));
    }

    change_painter = false;
    show_orbites = false;
    prev_painter = guro;

    try
    {
        std::string path("../../../../Contents/textures");
        PlanetSystem* sys = nullptr;
        VisibleObject* pl = nullptr;
        double base_orbit_ang = solar_system.getOrbitBaseAng();
        double base_sun_ang = solar_system.getSunBaseAng();
        reader.openFile("../../../../Contents/new.obj");
        Obj sph = reader.read();
        reader.openFile("../../../../Contents/ring.obj");
        Obj rng = reader.read();
        Dot3D<double> pl_cent;

        // orbite = reader.read("../../../../Contents/orbit_thicker.obj");

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

        pl_cent = pl->getPosDot();

        // Фобос
        pl = new Sphere;
        pl->setScale(radius_koef["phobos"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["phobos"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["mars"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["phobos"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["phobos"]*base_sun_ang);
        pl->setTexture(path+std::string("/mars/phobos.jpg"));
        sys->add(pl);

        // Деймос
        pl = new Sphere;
        pl->setScale(radius_koef["deimos"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["deimos"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["mars"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["deimos"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["deimos"]*base_sun_ang);
        pl->setTexture(path+std::string("/mars/deimos.jpg"));
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

        pl_cent = pl->getPosDot();

        // Ганимед
        pl = new Sphere;
        pl->setScale(radius_koef["ganimed"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["ganimed"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["jupiter"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["ganimed"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["ganimed"]*base_sun_ang);
        pl->setTexture(path+std::string("/jupiter/ganimed.jpg"));
        sys->add(pl);

        // Каллисто
        pl = new Sphere;
        pl->setScale(radius_koef["calisto"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["calisto"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["jupiter"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["calisto"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["calisto"]*base_sun_ang);
        pl->setTexture(path+std::string("/jupiter/calisto.jpg"));
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

        pl_cent = pl->getPosDot();

        // Титан
        pl = new Sphere;
        pl->setScale(radius_koef["titan"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["titan"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["saturn"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["titan"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["titan"]*base_sun_ang);
        pl->setTexture(path+std::string("/saturn/titan.jpg"));
        sys->add(pl);

        // Япет
        pl = new Sphere;
        pl->setScale(radius_koef["japet"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["japet"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["saturn"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["japet"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["japet"]*base_sun_ang);
        pl->setTexture(path+std::string("/saturn/japet.jpg"));
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

        pl_cent = pl->getPosDot();

        // Титания
        pl = new Sphere;
        pl->setScale(radius_koef["titania"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["titania"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["uranus"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["titania"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["titania"]*base_sun_ang);
        pl->setTexture(path+std::string("/uranus/titania.jpg"));
        sys->add(pl);

        // Оберон
        pl = new Sphere;
        pl->setScale(radius_koef["oberon"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["oberon"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["uranus"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["oberon"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["oberon"]*base_sun_ang);
        pl->setTexture(path+std::string("/uranus/oberon.jpg"));
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

        pl_cent = pl->getPosDot();

        // Тритон
        pl = new Sphere;
        pl->setScale(radius_koef["triton"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["triton"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["neptune"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["triton"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["triton"]*base_sun_ang);
        pl->setTexture(path+std::string("/neptune/triton.jpeg"));
        sys->add(pl);

        // Протей
        pl = new Sphere;
        pl->setScale(radius_koef["protei"]);
        pl->setTurningCent(pl_cent);
        pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef["protei"]);
        pl->setANG_PER_TICK_ROUND_SUN(sidereal_period["neptune"]*base_sun_ang);
        pl->setANG_PER_TICK_ROUND_ORBITE(period_of_orbit_rotation["protei"]*base_orbit_ang);
        pl->setANG_PER_TICK_ROUND_TURNCENT(sidereal_period["protei"]*base_sun_ang);
        pl->setTexture(path+std::string("/neptune/protei.jpg"));
        sys->add(pl);

        solar_system.add(sys);
        ////////////////////////////// !Нептун //////////////////////////////

        cam = new Camera(0, 0, -80000);

        light.setIa(255);
        light.setId(255);
    }
    catch(BaseErr&)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured while constructing Facade!");
        messageBox.setFixedSize(500,200);
    }

}

Facade::Facade(const char *name)
{
    reader.openFile(name);
}

Facade::~Facade()
{
    solar_system.clear();
    reader.closeFile();

    if (cam && (cam->getId() == Camera::free_cam))
    {
        delete cam;
    }

#ifdef TIME_TEST
    std::string txt;

    #ifdef TONE_SIMPLE
        txt += "Simple shading\n";
    #else
        txt += "Gouraud shading\n";
    #endif

    #ifdef MODEL_LOW
        txt += "Low poly model\n";
    #else
        #ifdef MODEL_MED
            txt += "Med poly model\n";
        #else
            txt += "High poly model\n";
        #endif
    #endif

   std::ofstream file("time_stat.txt");
   file << txt << (double) (tot_time / cnt) / CLOCKS_PER_SEC << " sec\n";
   file.close();
#endif
}

void Facade::showOrbites()
{
    show_orbites = !show_orbites;
}

void Facade::modelChange(int size)
{
    try
    {
        if (size == medium)
        {
            read("../../../../Contents/new_med.obj");
        }
        else if (size == normal)
        {
            read("../../../../Contents/new.obj");
        }
        else if (size == bad)
        {
            read("../../../../Contents/new_low.obj");
        }
    }
    catch (BaseErr& err)
    {
        read("../../../../Contents/new_med.obj");
    }
}

void Facade::painterChange()
{
    change_painter = true;
}

void Facade::camChange(int cam_num)
{
    if (cam_num == sun_cam)
    {
        if (cam->getId() == Camera::free_cam)
        {
            *cam = Camera(0, 0, -50000);
        }
        else
        {
            cam = new Camera(0, 0, -50000);
        }
    }
    else
    {
        cam = (*solar_system[cam_num])[0]->getCam();
    }
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
    gr.im.clrZBuf();
    gr.im.fill(Qt::black);

    Transformer trans;
    Obj draw_object;
    Dot3D<double> pl_cent;
    std::vector<double> I;

    if (change_painter)
    {
        if (prev_painter == guro)
        {
            prev_painter = solid;
            dr.changePainter(solid);
        }
        else
        {
            prev_painter = guro;
            dr.changePainter(guro);
        }
        change_painter = false;
    }

    /*
    if (show_orbites)
    {
        texture = new QImage("../../../../Contents/textures/white.png");
        pl_cent = Dot3D<double>(0, 0, 0);
        I = std::vector<double>(orbite.getPointsNum(), 250);

        for (auto it = distance_koef.begin(); it != distance_koef.end(); it++)
        {
            if (it->first == "moon") { continue; }
            draw_object = orbite;
            trans.scale(draw_object, EARTH_DISTANCE_FROM_SUN*it->second/100);
            trans.proectToCam(draw_object, *cam);
            trans.proectToCam(pl_cent, *cam);

            Drwr::GraphicsToDraw gr_in(gr.im, *cam, draw_object, texture, pl_cent, I, false);
            dr.draw(gr_in);
        }

        if (texture)
        {
            delete texture;
        }
    }
    */

    if (show_orbites)
    {
        for (auto it = distance_koef.begin(); it != distance_koef.end(); it++)
        {
            if (it->first == "moon" || it->first == "deimos" || it->first == "phobos" ||
                    it->first == "calisto" || it->first == "ganimed" || it->first == "deimos" ||
                    it->first == "japet" || it->first == "titan" || it->first == "oberon" ||
                    it->first == "titania" || it->first == "triton" || it->first == "protei") { continue; }
            Points3D draw_orbite = trans.scale(orbite, EARTH_DISTANCE_FROM_SUN*it->second / 100);
            trans.proectToCam(draw_orbite, *cam);

            Drwr::LinesToDraw to_dr(draw_orbite, *cam, gr.im);
            dr.draw(to_dr);
        }
//        Points3D draw_orbite = trans.scale(orbite, EARTH_DISTANCE_FROM_SUN*distance_koef["mercury"] / 100);
//        trans.proectToCam(draw_orbite, *cam);

//        Drwr::LinesToDraw to_dr(draw_orbite, *cam, gr.im);
//        dr.draw(to_dr);
    }

    VisibleObject* planet = nullptr;
    int i_for = solar_system.size();

#ifdef TIME_TEST
    i_for = 3;
    unsigned long long st = clock();

    #ifdef TONE_SIMPLE
        dr.changePainter(solid);
    #else
        dr.changePainter(guro);
    #endif


    #ifdef MODEL_LOW
        read("../../../../Contents/new_low.obj");
    #else
        #ifdef MODEL_MED
            read("../../../../Contents/new.obj");
        #else
            read("../../../../Contents/new_med.obj");
        #endif
    #endif

#endif
    for (int i = 0; i < i_for; i++)
    {
        for (int j = 0; j < solar_system[i]->size(); j++)
        {
            planet = (*solar_system[i])[j];
            pl_cent = planet->getPosDot();

            draw_object = planet->getTransformedObj();
            I = planet->calcI(light);
            trans.proectToCam(draw_object, *cam);
            trans.proectToCam(pl_cent, *cam);
            if (pl_cent.z <= 0)
            {
                continue;
            }

            texture = planet->getTexture();

            Drwr::GraphicsToDraw gr_in(gr.im, *cam, draw_object, texture, pl_cent, I, planet->isPlanet());

            dr.draw(gr_in);

            //trans.clear();
        }
    }

#ifdef TIME_TEST
    if (cnt <= 350)
    {
        tot_time += clock()-st;
        cnt++;
    }
#endif

}

void Facade::read(const char *name)
{
    reader.openFile(name);
    Obj tmp = reader.read();
    solar_system.setObj(tmp);
}
