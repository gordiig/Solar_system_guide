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

bool MyDisplay::isOnDisplay(const Dot2D<double> &left, const Dot2D<double> &right) const
{
    bool ans = true;
    if ((right.x < 0) || (left.y < 0) || (left.x > width()) || (right.y > height()))
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
        setPixelColor(x, y, col);
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
