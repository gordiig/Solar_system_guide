#include "drawer.h"
#include <thread>

using namespace Drwr;

void SolidPainter::paint(PolyToDraw &gr, const RasteredPoly &sorted_rastr)
{
    MathVector norm = Obj::calcOutNorm(gr.poly);
    norm.Ed();
    double I_total = 0;
    for (int i = 0; i < gr.I.size(); i++)
    {
        I_total += gr.I[i]/gr.poly.size();
    }

    if (I_total > 255)
    {
        I_total = 255;
    }

    for (int i = 0; i < sorted_rastr.size(); i++)
    {
        auto it_beg = sorted_rastr[i].begin();
        auto it_end = sorted_rastr[i].end();
        it_end--;

        double z = it_beg->z;
        double mz = ((it_end->x-it_beg->x) != 0) ?
                    ((it_end->z - it_beg->z) / (it_end->x-it_beg->x)) : 0;

        double l2 = sqrt((it_beg->x - it_end->x)*(it_beg->x - it_end->x) +
                         (it_beg->z - it_end->z)*(it_beg->z - it_end->z));

        for (int x = it_beg->x; x <= it_end->x; x++)
        {
            double l1 = sqrt((it_beg->x - x)*(it_beg->x - x) +
                             (it_beg->z - z)*(it_beg->z - z));
            double t = (l2 != 0) ? (l1/l2) : (1);

            double x_for_tex = (it_beg->texture_coord.x*(1-t) + it_end->texture_coord.x*t) * (gr.texture->width()-1);
            double y_for_tex = (it_beg->texture_coord.y*(1-t) + it_end->texture_coord.y*t) * (gr.texture->height()-1);

            int r, g, b;
            gr.texture->pixelColor(x_for_tex, y_for_tex).getRgb(&r, &g, &b);
            r = (double)r/256 * I_total;
            g = (double)g/256 * I_total;
            b = (double)b/256 * I_total;

            gr.im.putPixel(x, it_beg->y, z, QColor(r, g, b));

//                gr.im.putPixel(x, it_beg->y, z,
//                               QColor(I_total, I_total, I_total));
            z += mz;

        }
    }
}
void GuroPainter::paint(PolyToDraw &gr, const RasteredPoly &sorted_rastr)
{
    for (int i = 0; i < sorted_rastr.size(); i++)
    {
        auto it_beg = sorted_rastr[i].begin();
        auto it_end = sorted_rastr[i].end();
        it_end--;

        double z = it_beg->z;
        double mz = ((it_end->x-it_beg->x) != 0) ?
                    ((it_end->z - it_beg->z) / (it_end->x-it_beg->x)) : 0;

        double l2 = sqrt((it_beg->x - it_end->x)*(it_beg->x - it_end->x) +
                         (it_beg->z - it_end->z)*(it_beg->z - it_end->z));

        for (int x = it_beg->x; x <= it_end->x; x++)
        {
            double l1 = sqrt((it_beg->x - x)*(it_beg->x - x) +
                             (it_beg->z - z)*(it_beg->z - z));
            double t = (l2 != 0) ? (l1/l2) : (1);

            int I = it_beg->I*(1-t) + it_end->I*t;
//            if (I < 0)
//            {
//                I = 0;
//            }
//            else if (I > 255)
//            {
//                I = 255;
//            }

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

void Drawer::changePainter(int painter_num)
{
    if (painter) { delete painter; }

    if (painter_num == solid)
    {
        painter = new SolidPainter;
    }
    else if (painter_num == guro)
    {
        painter = new GuroPainter;
    }
    else
    {
        throw std::runtime_error("Wrong painter!!!\n");
    }
}

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

    // Рисовка
    try
    {
        painter->paint(gr, sorted_rastr);
        // solidPolyPainting(gr, sorted_rastr);
        // guroPolyPainting(gr, sorted_rastr);
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

void Drawer::drawLineBrez(MyDisplay &im, const Dot3D<double> &beg, const Dot3D<double> &end)
{
    DotForDrawer be(beg.x + 0.5, beg.y + 0.5, beg.z);
    DotForDrawer en(end.x + 0.5, end.y + 0.5, end.z);

    drawLineBrez(im, be, en);
}
void Drawer::drawLineBrez(MyDisplay &im, const DotForDrawer &beg, const DotForDrawer &end)
{
    int I = 100;
    int x = beg.x;
    int y = beg.y;
    double z = beg.z;
    int x_en = end.x;
    int y_en = end.y;
    double z_en = end.z;

    int dx = x_en - x;
    int dy = y_en - y;
    double dz = z_en - z;
    if (dx == 0 && dy == 0)
    {
        if (im.isOnDisplay(x, y))
        {
            im.putPixel(x, y, z, QColor(I, I, I));
        }
        return;
    }

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
    double mz = (dx == 0) ? (0) : (dz/dx);

    for (int i = 0; i <= dx; i++)
    {
        if (im.isOnDisplay(x, y))
        {
            im.putPixel(x, y, z, QColor(I, I, I));
        }

        while (e >= 0)
        {
            (ob == false) ? (y += sy) : (x += sx);
            e = e - 2*dx;
        }

        (ob == false) ? (x += sx) : (y += sy);
        e = e + 2*dy;
        z += mz;
    }
}

void Drawer::draw(GraphicsToDraw& gr)
{
    //drawScelet(gr.im, gr.obj);
    drawSphere(gr);
    //drawVizScelet(gr.im, gr.cam, gr.obj);
    //drawDots(gr.im, gr.obj.getPoints());
}
void Drawer::draw(LinesToDraw &gr)
{
    int size = gr.pts.size();
    for (int i = 0; i < size; i++)
    {
        int j = (i == size-1) ? (0) : (i+1);

        Line<double> line = Line<double>(gr.pts[i], gr.pts[j]);

        gr.cam.lineCut(line);
        if ((line.beg.x == -1) && (line.beg.y == -1) && (line.beg.z == -1))
        {
            continue;
        }

        if (line.beg.z != 0)
        {
            line.beg.x *= (gr.cam.getDistanceToScreen() / line.beg.z);
            line.beg.y *= (gr.cam.getDistanceToScreen() / line.beg.z);
        }
        if (line.end.z != 0)
        {
            line.end.x *= (gr.cam.getDistanceToScreen() / line.end.z);
            line.end.y *= (gr.cam.getDistanceToScreen() / line.end.z);
        }
        line.beg.x += gr.im.width()/2;
        line.beg.y += gr.im.height()/2;
        line.end.x += gr.im.width()/2;
        line.end.y += gr.im.height()/2;

        gr.im.screenCut(line);
        if ((line.beg.x == -1) && (line.beg.y == -1) && (line.beg.z == -1))
        {
            continue;
        }

        drawLineBrez(gr.im, line.beg, line.end);
    }
}
