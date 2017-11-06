#include "facade.h"

Facade::Facade()
{

    /*
    radius_koef = {{'m', 0.500},
                   {'v', 0.950},
                   {'e', 1.000},
                   {'M', 0.700},
                   {'j', 5.970},
                   {'s', 4.140},
                   {'u', 2.000},
                   {'n', 1.950},
                   {'S', 10.5}};
                   */

    radius_koef = {{'m', 5.000},
                   {'v', 9.600},
                   {'e', 10.00},
                   {'M', 8.000},
                   {'j', 38.70},
                   {'s', 33.40},
                   {'u', 20.00},
                   {'n', 19.50},
                   {'S', 218.0}};

    distance_koef = {{'m', 0.387},
                     {'v', 0.723},
                     {'e', 1.000},
                     {'M', 1.524},
                     {'j', 3.004},
                     {'s', 5.252},
                     {'u', 7.19},
                     {'n', 9.07}};

    std::string path("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/textures");
    PlanetSystem* sys = nullptr;
    Sphere* pl = nullptr;


    ////////////////////////////// Солнце //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setKa(0.95);
    pl->setKd(0);
    pl->setScale(radius_koef['S']);
    pl->setTexture(path+std::string("/sun.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Солнце //////////////////////////////


    ////////////////////////////// Меркурий //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['m']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN*distance_koef['m']);
    //pl->setX(2000);
    pl->setTexture(path+std::string("/mercury/mercury.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Меркурий //////////////////////////////



    ////////////////////////////// Венера //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['v']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['v']);
    //pl->setX(-2000);
    pl->setTexture(path+std::string("/venus/venus.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Венера //////////////////////////////


    ////////////////////////////// Земля //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['e']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['e']);
    //pl->setX(4000);
    pl->setTexture(path+std::string("/earth/earth.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Земля //////////////////////////////

    ////////////////////////////// Марс //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['M']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['M']);
    //pl->setX(-4000);
    pl->setTexture(path+std::string("/mars/mars.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Марс //////////////////////////////


    ////////////////////////////// Юпитер //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['j']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['j']);
    //pl->setX(6000);
    pl->setTexture(path+std::string("/jupiter/jupiter.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Юпитер //////////////////////////////


    ////////////////////////////// Сатурн //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['s']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['s']);
    //pl->setX(-6000);
    pl->setTexture(path+std::string("/saturn/saturn.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Сатурн //////////////////////////////


    ////////////////////////////// Уран //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['u']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['u']);
    //pl->setX(8000);
    pl->setTexture(path+std::string("/uranus/uranus.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Уран //////////////////////////////


    ////////////////////////////// Нептун //////////////////////////////
    sys = new PlanetSystem;

    pl = new Sphere;
    pl->setScale(radius_koef['n']);
    pl->setZ(-EARTH_DISTANCE_FROM_SUN * distance_koef['n']);
    //pl->setX(-8000);
    pl->setTexture(path+std::string("/neptune/neptune.jpg"));
    sys->add(pl);

    solar_system.add(sys);
    ////////////////////////////// !Нептун //////////////////////////////

    cam.setZ(-50000);


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
    reader.closeFile();
}

void Facade::camMove(GraphStruct &gr, InterfaceCommand *caps)
{
    if (caps)
    {
        caps->exec(cam);
    }
    light.setX(0);
    light.setY(0);
    light.setZ(0);

    draw(gr);
}

void Facade::planetMove(GraphStruct &gr)
{
    solar_system.tickMove();
    light.setX(0);
    light.setY(0);
    light.setZ(0);

    draw(gr);
}

void Facade::draw(GraphStruct &gr)
{
//    light.setIa(gr.Ia);
//    light.setId(gr.Id);
    light.setIa(255);
    light.setId(255);

    Drawer dr;
    gr.im.clrZBuf();
    gr.im.fill(Qt::black);
    for (int i = 0; i < solar_system.size(); i++)
    {
        for (int j = 0; j < solar_system[i]->size(); j++)
        {
            Sphere* planet = (*solar_system[i])[j];

            Transformer trans;
            Obj draw_object(trans.transform(*planet, cam), planet->getTexCord(), planet->getPoly());
            light.setByDot(trans.transform(light, cam));

            //    planet->setKa(gr.ka);
            //    planet->setKd(gr.kd);

            texture = planet->getTexture();

            Drwr::GraphicsToDraw gr_in(gr.im, cam, light, draw_object, texture,
                           planet->getKa(), planet->getKd());
            dr.draw(gr_in);
        }
    }
}

void Facade::read(const char *name)
{
    reader.openFile(name);
    Obj tmp = reader.read();
    solar_system.setObj(tmp);
}
