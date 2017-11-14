#include "mydisplay.h"

MyDisplay::MyDisplay() : QImage() { }
MyDisplay::MyDisplay(int width, int height, QImage::Format format) : QImage(width, height, format)
{
    z_buf = MyMat<double>(height, width, 99999999999999);
}

MyDisplay::~MyDisplay()
{
    z_buf.clear();
}

void MyDisplay::screenCut(Points3D &in_poly, std::vector<double>& in_I, Points2D& in_tex_coords)
{
    for (int i = 0; i < 4; i++)
    {
        screenCut(in_poly, in_I, in_tex_coords, i);
        if (in_poly.empty())
        {
            break;
        }
    }

}
void MyDisplay::screenCut(Points3D &in_poly, std::vector<double>& in_I, Points2D& in_tex_coords, int side)
{
    Points3D ans;
    std::vector<double> ans_I;
    Points2D ans_tex;
    Line<double> scr_line, poly_line;
    if (side == left)
    {
        scr_line.beg = Dot3D<double>(0, height()-1, 0);
        scr_line.end = Dot3D<double>(0, 0, 0);
    }
    else if (side == top)
    {
        scr_line.beg = Dot3D<double>(0, 0, 0);
        scr_line.end = Dot3D<double>(width()-1, 0, 0);
    }
    else if (side == right)
    {
        scr_line.beg = Dot3D<double>(width()-1, 0, 0);
        scr_line.end = Dot3D<double>(width()-1, height()-1, 0);
    }
    else if (side == bottom)
    {
        scr_line.beg = Dot3D<double>(width()-1, height()-1, 0);
        scr_line.end = Dot3D<double>(0, height()-1, 0);
    }
    else
    {
       in_poly.clear();
    }

    Dot3D<double> first_dot = in_poly[0];
    Dot2D<double> first_tex = in_tex_coords[0];
    double first_I = in_I[0];

    Dot3D<double> beg_dot, end_dot;
    Dot2D<double> beg_tex, end_tex;
    double beg_I, end_I;
    for (int i = 0; i < in_poly.size(); i++)
    {
        beg_dot = in_poly[i];
        end_dot = (i == (in_poly.size() - 1)) ? (first_dot) : (in_poly[i+1]);
        beg_tex = in_tex_coords[i];
        end_tex = (i == (in_poly.size() - 1)) ? (first_tex) : (in_tex_coords[i+1]);
        beg_I = in_I[i];
        end_I = (i == (in_poly.size() - 1)) ? (first_I) : (in_I[i+1]);

        poly_line.beg = beg_dot;
        poly_line.end = end_dot;

        if (isDotInSide(beg_dot, side) && isDotInSide(end_dot, side))
        {
            ans.push_back(end_dot);
            ans_tex.push_back(end_tex);
            ans_I.push_back(end_I);
        }
        else if (isDotInSide(beg_dot, side) && !isDotInSide(end_dot, side))
        {
            double t = MathFunctions::lineIntersection2D(poly_line, scr_line);
            Dot3D<double> to_push(beg_dot.x + t*(end_dot.x - beg_dot.x),
                                  beg_dot.y + t*(end_dot.y - beg_dot.y),
                                  beg_dot.z + t*(end_dot.z - beg_dot.z));
            Dot2D<double> to_push_tex(beg_tex.x + t*(end_tex.x - beg_tex.x),
                                      beg_tex.y + t*(end_tex.y - beg_tex.y));

            if (!isDotOnScreen(to_push))
            {
                int asss;
                asss = 0;
            }

            ans.push_back(to_push);
            ans_tex.push_back(to_push_tex);
            ans_I.push_back(beg_I + t*(end_I - beg_I));
        }
        else if (!isDotInSide(beg_dot, side) && isDotInSide(end_dot, side))
        {
            double t = MathFunctions::lineIntersection2D(poly_line, scr_line);
            Dot3D<double> to_push(beg_dot.x + t*(end_dot.x - beg_dot.x),
                                  beg_dot.y + t*(end_dot.y - beg_dot.y),
                                  beg_dot.z + t*(end_dot.z - beg_dot.z));
            Dot2D<double> to_push_tex(beg_tex.x + t*(end_tex.x - beg_tex.x),
                                      beg_tex.y + t*(end_tex.y - beg_tex.y));

            if (!isDotOnScreen(to_push))
            {
                int asss;
                asss = 0;
            }

            ans.push_back(to_push);
            ans_tex.push_back(to_push_tex);
            ans_I.push_back(beg_I + t*(end_I - beg_I));
            ans.push_back(end_dot);
            ans_tex.push_back(end_tex);
            ans_I.push_back(end_I);
        }
    }

    in_poly = ans;
    in_tex_coords = ans_tex;
    in_I = ans_I;
}

bool MyDisplay::isOnDisplay(const Dot2D<double> &left, const Dot2D<double> &right) const
{
    bool ans = true;
    if ((right.x < 0) || (left.y < 0) || (left.x >= width()) || (right.y >= height()))
    {
        ans = false;
    }

    return ans;
}
bool MyDisplay::isOnDisplay(const DotForDrawer &point) const
{
    return isOnDisplay(point.x, point.y);
}
bool MyDisplay::isOnDisplay(const int x, const int y) const
{
    bool ans = false;
    if ((x + width()/2 < width()) && (x + width()/2 > 0) &&
            (y + height()/2 < height()) && (y + height()/2 > 0))
    {
        ans = true;
    }

    return ans;
}

bool MyDisplay::isDotOnScreen(const Dot3D<double> &in) const
{
    Dot2D<double> tmp(in.x, in.y);
    return isDotOnScreen(tmp);
}
bool MyDisplay::isDotOnScreen(const Dot2D<double> &in) const
{
    return ((in.x >= 0) && (in.x < width()) && (in.y >= 0) && (in.y < height()));
}

bool MyDisplay::isDotInSide(const Dot3D<double> & dot, int side) const
{
    bool ans = false;
    if (side == left)
    {
        ans = dot.x >= 0;
    }
    else if (side == top)
    {
        ans = dot.y >= 0;
    }
    else if (side == right)
    {
        ans = dot.x < width();
    }
    else if (side == bottom)
    {
        ans = dot.y < height();
    }

    return ans;
}

void MyDisplay::putPixel(const DotForDrawer &dot, const QColor &col)
{
    putPixel(dot.x, dot.y, dot.z, col);
}
void MyDisplay::putPixel(const int x, const int y, const double z, const QColor &col)
{
    if (z <= z_buf[y][x])
    {
        //setPixelColor(x, y, col);
        QRgb* pix = (QRgb*) this->bits();
        pix[y*width()+x] = qRgb(col.red(), col.green(), col.blue());
        z_buf[y][x] = z;
    }
}

void MyDisplay::fillZBuf(const double in)
{
    z_buf.fill(in);
}
void MyDisplay::clrZBuf()
{
    z_buf.fill(99999999999999);
}
