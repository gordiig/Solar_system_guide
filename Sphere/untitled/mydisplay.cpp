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
    MathVector side_vector, beg_point_vector, end_point_vector;
    Dot3D<double> scr_beg_dot, scr_end_dot;
    if (side == left)
    {
        side_vector.setY(-height());
        end_point_vector.setY(-height());
        beg_point_vector.setY(-height());
        scr_beg_dot.y = height();
    }
    else if (side == top)
    {
        side_vector.setX(width());
        scr_end_dot.x = width();
    }
    else if (side == right)
    {
        side_vector.setY(height());
        end_point_vector.setX(-width());
        beg_point_vector.setX(-width());
        scr_beg_dot.x = width();
        scr_end_dot.x = width();
        scr_end_dot.y = height();
    }
    else if (side == bottom)
    {
        side_vector.setX(-width());
        end_point_vector.setX(-width());
        end_point_vector.setY(-height());
        beg_point_vector.setX(-width());
        beg_point_vector.setY(-height());
        scr_beg_dot.x = width();
        scr_beg_dot.y = height();
        scr_end_dot.y = height();
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

        end_point_vector.setX(end_point_vector.getX() + end_dot.x);
        end_point_vector.setY(end_point_vector.getY() + end_dot.y);
        beg_point_vector.setX(beg_point_vector.getX() + beg_dot.x);
        beg_point_vector.setY(beg_point_vector.getY() + beg_dot.y);

        double beg_mult = side_vector.vectMult(beg_point_vector).len();
        double end_mult = side_vector.vectMult(end_point_vector).len();

        if ((beg_mult > 0) && (end_mult > 0)) // Обе внутри
        {
            ans.push_back(end_dot);
            ans_tex.push_back(end_tex);
            ans_I.push_back(end_I);
        }
        else if ((beg_mult > 0) && (end_mult <= 0)) // Рассматриваемая вне
        {
            double t = MathFunctions::lineIntersection2D(Line<double>(beg_dot, end_dot),
                                                         Line<double>(scr_beg_dot, scr_end_dot));
            if ((t < 0) || (t > 1))
            {
                continue;
            }

            Dot3D<double> cut_dot(beg_dot.x + (end_dot.x-beg_dot.x)*t,
                                  beg_dot.y + (end_dot.y-beg_dot.y)*t,
                                  beg_dot.z + (end_dot.z-beg_dot.z)*t);

            Dot2D<double> cut_tex(beg_tex.x + (end_tex.x-beg_tex.x)*t,
                                  beg_tex.y + (end_tex.y-beg_tex.y)*t);

            double cut_I = beg_I + (end_I-beg_I)*t;

            ans.push_back(cut_dot);
            ans_tex.push_back(cut_tex);
            ans_I.push_back(cut_I);
        }
        else if ((beg_mult <= 0) && (end_mult > 0)) // Начальная вне
        {
            double t = MathFunctions::lineIntersection2D(Line<double>(beg_dot, end_dot),
                                                         Line<double>(scr_beg_dot, scr_end_dot));
            if ((t < 0) || (t > 1))
            {
                continue;
            }

            Dot3D<double> cut_dot(beg_dot.x + (end_dot.x-beg_dot.x)*t,
                                  beg_dot.y + (end_dot.y-beg_dot.y)*t,
                                  beg_dot.z + (end_dot.z-beg_dot.z)*t);

            Dot2D<double> cut_tex(beg_tex.x + (end_tex.x-beg_tex.x)*t,
                                  beg_tex.y + (end_tex.y-beg_tex.y)*t);

            double cut_I = beg_I + (end_I-beg_I)*t;

            ans.push_back(cut_dot);
            ans.push_back(end_dot);
            ans_tex.push_back(cut_tex);
            ans_tex.push_back(end_tex);
            ans_I.push_back(cut_I);
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
