#include "drawer.h"

using namespace Drwr;

void Drawer::drawDots(MyDisplay& im, const Points3D& dots)
{
    for (int i = 0; i < dots.size(); i++)
    {
        int x = dots[i].x + im.width()/2;
        int y = dots[i].y + im.height()/2;
        im.setPixelColor(x, y, QColor(Qt::blue));
    }
}
void Drawer::drawScelet(MyDisplay& im, const Obj &obj)
{
    std::list<int>::const_iterator it;
    std::list<int>::const_iterator it_nxt;
    auto points = obj.getPoints();
    auto poly = obj.getPoly();

    for (int i = 0; i < poly.size(); i++)
    {
        it_nxt = poly[i].begin(); it_nxt++;
        for (it = poly[i].begin(); it_nxt != poly[i].end(); it++, it_nxt++)
        {
            drawLineBrez(im, points[*it-1], points[*it_nxt-1]);
        }
        it_nxt = poly[i].begin();
        drawLineBrez(im, points[*it-1], points[*it_nxt-1]);
    }
}
void Drawer::drawVizScelet(MyDisplay &im, const Camera& cam, const Obj &obj)
{
    std::list<int>::const_iterator it;
    std::list<int>::const_iterator it_nxt;
    auto points = obj.getPoints();
    auto poly = obj.getPoly();

    for (int i = 0; i < poly.size(); i++)
    {
        if (cam.isPolyViz(obj.makeCut(i)))
        {
            for (it = poly[i].begin(), it_nxt = it, it_nxt++; it_nxt != poly[i].end(); it++, it_nxt++)
            {
                drawLineBrez(im, points[*it-1], points[*it_nxt-1]);
            }
            it_nxt = poly[i].begin();
            drawLineBrez(im, points[*it-1], points[*it_nxt-1]);
        }
    }
}
void Drawer::drawSphere(GraphicsToDraw &gr)
{
    auto poly = gr.obj.getPoly();

    for (int i = 0; i < poly.size(); i++)
    {
        if (gr.cam.isPolyViz(gr.obj.makeCut(i), gr.c_d, gr.is_planet))
        {
            PolyToDraw tmp(gr, i);
            drawPoly(tmp);
        }
    }
}

void Drawer::drawPoly(PolyToDraw &gr)
{
    RasteredPoly sorted_rastr = polyRasterization(gr);
    if (sorted_rastr.empty())
    {
        return;
    }

    // Рисовка
    try
    {
        //solidPolyPainting(gr, sorted_rastr);
        guroPolyPainting(gr, sorted_rastr);
    }
    catch(BaseErr&)
    {
        for (auto &x : sorted_rastr)
        {
            x.clear();
        }

        throw ColorIntenseErr("\nDrawer::drawPoly() in drawer.cpp");
    }
}
RasteredPoly Drawer::polyRasterization(PolyToDraw &in)
{
    // Приведение к экранным координатам и проверка на невидимость полигона в окне
    double z_min = in.poly[0].z;
    for (auto &x : in.poly)
    {
        if (x.z != 0)
        {
            x.x *= (in.cam.getDistanceToScreen() / x.z);
            x.y *= (in.cam.getDistanceToScreen() / x.z);
        }

        x.x += in.im.width() / 2;
        x.y += in.im.height() / 2;

        z_min = (z_min > x.z) ? (x.z) : (z_min);
    }

    in.im.screenCut(in.poly, in.I, in.tex_coords);
    if (in.poly.empty() || (!in.cam.isOnDisplay(z_min)))
    {
        return RasteredPoly();
    }

    std::list<DotForDrawer> rastr;
    int max_y = MathFunctions::doubleToInt(in.poly[0].y);
    int min_y = MathFunctions::doubleToInt(in.poly[0].y);

    // Растеризация полигона
    // С помощью алгоритма Брезенхема создается список точек для каждого отрезка
    for (int i = 0; i < in.poly.size(); i++)
    {
        max_y = (max_y < in.poly[i].y) ? (MathFunctions::doubleToInt(in.poly[i].y)) : (max_y);
        min_y = (min_y > in.poly[i].y) ? (MathFunctions::doubleToInt(in.poly[i].y)) : (min_y);

        int j = (i == in.poly.size()-1) ? (0) : (i+1);

//        // Тут in.poly[i].x потому что камеру мы не двигаем в коорд экрана
//        double I1 = in.light.getIa()*in.ka + in.light.calcDiffuse(in.poly[i], norm1.getEd())*in.kd;
//        double I2 = in.light.getIa()*in.ka + in.light.calcDiffuse(in.poly[j], norm2.getEd())*in.kd;
        double I1 = in.I[i];
        double I2 = in.I[j];

        DotForDrawer in1(in.poly[i].x, in.poly[i].y, in.poly[i].z, I1, in.tex_coords[i]);
        DotForDrawer in2(in.poly[j].x, in.poly[j].y, in.poly[j].z, I2, in.tex_coords[j]);
        std::list<DotForDrawer> tmp = lineRasterizationBrez(in1, in2);
        if (!tmp.empty())
        {
            rastr.insert(rastr.end(), tmp.begin(), tmp.end());
        }
    }

    // Сортировка по Оу
    // Создание вектора, итый элемент которого -- список точек на итой строке
    RasteredPoly sorted_rastr;
    for (int y = min_y; y <= max_y; y++)
    {
        std::list<DotForDrawer> tmp;
        for (auto &ob : rastr)
        {
            if (ob.y == y)
            {
                tmp.push_back(ob);
            }
        }

        if (!tmp.empty())
        {
            sorted_rastr.push_back(tmp);
        }
    }
    // Сортировка по Ох
    for (int i = 0; i < sorted_rastr.size(); i++)
    {
        sorted_rastr[i].sort();

        if (((i == 0) || (i == sorted_rastr.size()-1)) && (sorted_rastr[i].size() == 1))
        {
            sorted_rastr[i].push_back(*(sorted_rastr[i].begin()));
        }
        /*
        if ((i != 0) && (i != sorted_rastr.size()-1))
        {
            sorted_rastr[i].unique();
        }
        */
    }

    return sorted_rastr;
}

void Drawer::solidPolyPainting(PolyToDraw &gr, const RasteredPoly &sorted_rastr)
{
    MathVector norm = Obj::calcOutNorm(gr.poly);
    norm.Ed();
    double x_c = 0, y_c = 0, z_c = 0;
    for (int i = 0; i < gr.poly.size(); i++)
    {
        x_c += gr.poly[i].x / gr.poly.size();
        y_c += gr.poly[i].y / gr.poly.size();
        z_c += gr.poly[i].z / gr.poly.size();
    }

    //double Id = gr.light.calcDiffuse(Dot3D<double>(x_c, y_c, z_c), norm) * gr.kd;
    double Id = 255;
    if (Id < 0)
    {
        Id = 0;
    }

    //double I_total = Id + gr.light.getIa()*gr.ka;
    double I_total = 255;
    if (I_total > 255)
    {
        throw ColorIntenseErr("\nDrawer::drawPoly() in drawer.cpp");
    }

    for (int i = 0; i < sorted_rastr.size(); i++)
    {
        auto it_beg = sorted_rastr[i].begin();
        auto it_end = sorted_rastr[i].end();
        it_end--;

        double z = it_beg->z;
        double mz = ((it_end->x-it_beg->x) != 0) ?
                    ((it_end->z - it_beg->z) / (it_end->x-it_beg->x)) : 0;

        for (int x = it_beg->x; x <= it_end->x; x++)
        {
            z += mz;
            if (gr.im.isOnDisplay(x-gr.im.width()/2, it_beg->y-gr.im.height()/2) &&
                    gr.cam.isOnDisplay(z))
            {
                gr.im.putPixel(x, it_beg->y, z,
                                     QColor(I_total, I_total, I_total));
            }
        }
    }
}
void Drawer::guroPolyPainting(PolyToDraw &gr, const RasteredPoly &sorted_rastr)
{
    for (int i = 0; i < sorted_rastr.size(); i++)
    {
        auto it_beg = sorted_rastr[i].begin();
        auto it_end = sorted_rastr[i].end();
        it_end--;

        double z = it_beg->z;
        double mz = ((it_end->x-it_beg->x) != 0) ?
                    ((it_end->z - it_beg->z) / (it_end->x-it_beg->x)) : 0;

        for (int x = it_beg->x; x <= it_end->x; x++)
        {
            double l1 = sqrt((it_beg->x - x)*(it_beg->x - x) +
                             (it_beg->z - z)*(it_beg->z - z));
            double l2 = sqrt((it_beg->x - it_end->x)*(it_beg->x - it_end->x) +
                             (it_beg->z - it_end->z)*(it_beg->z - it_end->z));
            double t = (l2 != 0) ? (l1/l2) : (1);

            int I = it_beg->I*(1-t) + it_end->I*t;
            if (I < 0)
            {
                I = 0;
            }
            else if (I > 255)
            {
                I = 255;
            }

            double x_for_tex = (it_beg->texture_coord.x*(1-t) + it_end->texture_coord.x*t) * (gr.texture->width()-1);
            double y_for_tex = (it_beg->texture_coord.y*(1-t) + it_end->texture_coord.y*t) * (gr.texture->height()-1);

            int r, g, b;
            gr.texture->pixelColor(x_for_tex, y_for_tex).getRgb(&r, &g, &b);
            r = (double)r/256 * I;
            g = (double)g/256 * I;
            b = (double)b/256 * I;

            gr.im.putPixel(x, it_beg->y, z, QColor(r, g, b));
            //gr.im.putPixel(x, it_beg->y, z, QColor(I, I, I));


            z += mz;
        }
    }
}

std::list<DotForDrawer> Drawer::lineRasterizationBrez(const DotForDrawer& st_dot,
                                                            const DotForDrawer& en_dot)
{
    std::list<DotForDrawer> rastr;

    double I = st_dot.I;
    int x = MathFunctions::doubleToInt(st_dot.x);
    int dx = MathFunctions::doubleToInt(en_dot.x) - x;
    int y = MathFunctions::doubleToInt(st_dot.y);
    int dy = MathFunctions::doubleToInt(en_dot.y) - y;
    if (dy == 0)
    {
        return rastr;
    }

    int sx = MathFunctions::SIGN(dx);
    int sy = MathFunctions::SIGN(dy);
    dx = abs(dx);
    dy = abs(dy);

    bool ob = false;
    if (dy > dx)
    {
        ob = true;
        std::swap(dx, dy);
    }

    double z = st_dot.z;
    double m_z = (en_dot.z - z) / dx;

    double m_x_tex = (en_dot.texture_coord.x - st_dot.texture_coord.x) / dx;
    double m_y_tex = (en_dot.texture_coord.y - st_dot.texture_coord.y) / dx;
    Dot2D<double> tex_c(st_dot.texture_coord);

    int e = 2*dy - dx;

    for (int i = 0; i <= dx; i++)
    {
        DotForDrawer tmp(x, y, z, I, tex_c);
        rastr.push_back(tmp);

        while (e >= 0)
        {
            (ob == false) ? (y += sy) : (x += sx);
            e = e - 2*dx;
        }

        (ob == false) ? (x += sx) : (y += sy);
        e = e + 2*dy;

        z += m_z;
        tex_c.x += m_x_tex;
        tex_c.y += m_y_tex;
        I = MathFunctions::lineInterpolationIntens(st_dot, en_dot, DotForDrawer(x, y, z));
        //tex_c = MathFunctions::lineInterpolationTex(st_dot, en_dot, DotForDrawer(x, y, z));
    }

    return rastr;
}

void Drawer::drawLineBrez(MyDisplay &im, const int x_st, const int y_st, const int x_en, const int y_en)
{
    int x = x_st;
    int y = y_st;
    if ((x == x_en) && (y == y_en))
    {
        if (im.isOnDisplay(x, y))
        {
            im.setPixelColor(x + im.width()/2, y + im.height()/2, QColor(Qt::red));
        }
        return;
    }

    int dx = x_en - x;
    int dy = y_en - y;
    int sx = (dx >= 0) ? (1) : (-1);
    int sy = (dy >= 0) ? (1) : (-1);
    dx = abs(dx);
    dy = abs(dy);

    bool ob = false;
    if (dy > dx)
    {
        ob = true;
        std::swap(dx, dy);
    }

    int e = 2*dy - dx;

    for (int i = 0; i <= dx; i++)
    {
        if (im.isOnDisplay(x, y))
        {
            im.setPixelColor(x + im.width()/2, y + im.height()/2, QColor(Qt::red));
        }

        while (e >= 0)
        {
            (ob == false) ? (y += sy) : (x += sx);
            e = e - 2*dx;
        }

        (ob == false) ? (x += sx) : (y += sy);
        e = e + 2*dy;
    }

}
void Drawer::drawLineBrez(MyDisplay &im, const Dot2D<double> &st, const Dot2D<double> &en)
{
    int x_st = st.x + 0.5;
    int y_st = st.y + 0.5;
    int x_en = en.x + 0.5;
    int y_en = en.y + 0.5;
    drawLineBrez(im, x_st, y_st, x_en, y_en);
}

void Drawer::draw(GraphicsToDraw& gr)
{
    //drawScelet(gr.im, gr.obj);
    drawSphere(gr);
    //drawVizScelet(gr.im, gr.cam, gr.obj);
    //drawDots(gr.im, gr.obj.getPoints());
}
