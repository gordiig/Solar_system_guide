#ifndef MATH_ABSTRACTS_H
#define MATH_ABSTRACTS_H

#include "baseobjects.h"
#include <math.h>

class MathFunctions
{
public:
    template <typename T>
    static int SIGN(const T& in)
    {
        return (in >= 0) ? (1) : (-1);
    }

    static int doubleToInt(const double in)
    {
        return (int) (in + (double)0.5*SIGN(in));
    }

    static double lineInterpolationIntens(const DotForDrawer& st_dot, const DotForDrawer& en_dot, const DotForDrawer& cur_dot)
    {
        double l1 = sqrt((st_dot.x - cur_dot.x)*(st_dot.x - cur_dot.x) +
                         (st_dot.y - cur_dot.y)*(st_dot.y - cur_dot.y) +
                         (st_dot.z - cur_dot.z)*(st_dot.z - cur_dot.z));
        double l2 = sqrt((en_dot.x - st_dot.x)*(en_dot.x - st_dot.x) +
                         (en_dot.y - st_dot.y)*(en_dot.y - st_dot.y) +
                         (en_dot.z - st_dot.z)*(en_dot.z - st_dot.z));
        double t = (l2 != 0) ? (l1/l2) : (1);

        return st_dot.I*(1-t) + t*en_dot.I;
    }

    static Dot2D<double> lineInterpolationTex(const DotForDrawer& st_dot, const DotForDrawer& en_dot,
                                              const DotForDrawer& cur_dot)
    {
        double l1 = abs(cur_dot.x - st_dot.x);
        double l2 = abs(en_dot.x - st_dot.x);
        double t = (l2 != 0) ? (l1/l2) : (1);
        double ans1 = st_dot.texture_coord.x*(1-t) + t*en_dot.texture_coord.x;

        l1 = abs(cur_dot.y - st_dot.y);
        l2 = abs(en_dot.y - st_dot.y);
        t = (l2 != 0) ? (l1/l2) : (1);
        double ans2 = st_dot.texture_coord.y*(1-t) + t*en_dot.texture_coord.y;

        return Dot2D<double>(ans1, ans2);
    }
};

class MathVector : public BaseObject
{
public:
    MathVector();
    MathVector(const MathVector&);
    MathVector(MathVector&&);
    MathVector(double, double, double);
    MathVector(double, double, double, double, double, double);
    MathVector(const Dot3D<double>&);
    MathVector(const Dot3D<double>&, const Dot3D<double>&);

    MathVector& operator = (const MathVector&);
    MathVector& operator = (MathVector&&);

    double len() const;
    double scalarMult(const MathVector&) const;

    MathVector& invert();
    MathVector getInvert() const;
    MathVector& Ed();
    MathVector getEd() const;
};

template <typename T>
class MyMat
{
private:
    std::vector<std::vector<T> > arr;
    int str;
    int col;

public:
    MyMat() : str(0), col(0) { }
    MyMat(const MyMat<T>& in)
    {
        for (auto &x : in.arr)
        {
            arr.push_back(x);
        }
    }
    MyMat(MyMat<T>&& in)
    {
        for (auto &x : in.arr)
        {
            arr.push_back(x);
        }

        in.clear();
    }
    MyMat(int in_str, int in_col, const T& fill = 0)
    {
        str = in_str;
        col = in_col;
        for (int i = 0; i < str; i++)
        {
            std::vector<T> tmp;
            for (int j = 0; j < col; j++)
            {
                tmp.push_back(fill);
            }
            arr.push_back(tmp);
        }
    }
    ~MyMat()
    {
        arr.clear();
    }

    MyMat<T>& operator = (const MyMat& in)
    {
        clear();
        for (int i = 0; i < in.size(); i++)
        {
            arr.push_back(in[i]);
        }

        return (*this);
    }
    MyMat<T>& operator = (MyMat&& in)
    {
        clear();
        for (int i = 0; i < in.size(); i++)
        {
            arr.push_back(in[i]);
        }
        in.clear();

        return (*this);
    }

    std::vector<T>& operator [] (int i)
    {
        return arr[i];
    }
    std::vector<T> operator [] (int i) const
    {
        return arr[i];
    }

    MyMat<T>& operator - ()
    {
        for (auto &x : arr)
        {
            for (auto &y : x)
            {
                y = -y;
            }
        }

        return (*this);
    }

    MyMat<T> operator + (const MyMat<T>& in) const
    {
        if ((str != in.str) && (col != in.col))
        {
            throw MatSizeErr("in operator +, in file math_abstr.h");
        }

        MyMat<T> ans(str, col, 0);
        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < col; j++)
            {
                ans[i][j] = arr[i][j] + in[i][j];
            }
        }

        return ans;
    }
    MyMat<T>& operator += (const MyMat<T>& in)
    {
        if ((str != in.str) && (col != in.col))
        {
            throw MatSizeErr("in operator +=, in file math_abstr.h");
        }

        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < col; j++)
            {
                arr[i][j] += in[i][j];
            }
        }

        return (*this);
    }
    MyMat<T> operator - (const MyMat<T>& in) const
    {
        if ((str != in.str) && (col != in.col))
        {
            throw MatSizeErr("in operator -, in file math_abstr.h");
        }

        MyMat<T> ans(str, col, 0);
        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < col; j++)
            {
                ans[i][j] = arr[i][j] - in[i][j];
            }
        }

        return ans;
    }
    MyMat<T>& operator -= (const MyMat<T>& in)
    {
        if ((str != in.str) && (col != in.col))
        {
            throw MatSizeErr("in operator -=, in file math_abstr.h");
        }

        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < col; j++)
            {
                arr[i][j] = in[i][j];
            }
        }

        return (*this);
    }

    MyMat<T> operator * (const MyMat<T>& in) const
    {
        if (col != in.str)
        {
            throw MatSizeErr("in operator *, in file math_abstr.h");
        }

        MyMat<T> ans(str, in.col, 0);
        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < in.col; j++)
            {
                for (int k = 0; k < col; k++)
                {
                    ans[i][j] += arr[i][k] * in.arr[k][j];
                }
            }
        }

        return ans;
    }
    MyMat<T>& operator *= (const MyMat<T>& in)
    {
        if (col != in.str)
        {
            throw MatSizeErr("in operator *=, in file math_abstr.h");
        }

        MyMat<T> ans(str, in.col, 0);
        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < in.col; j++)
            {
                for (int k = 0; k < col; k++)
                {
                    ans[i][j] += arr[i][k] * in.arr[k][j];
                }
            }
        }

        (*this) = ans;

        return (*this);
    }

    void fill(const T& in)
    {
        for (auto &x : arr)
        {
            for (auto &y : x)
            {
                y = in;
            }
        }
    }
    void clear()
    {
        for (auto &x : arr)
        {
            x.clear();
        }
        arr.clear();
    }

    int size() const { return arr.size(); }
    int fullSize() const { return arr.size()*arr[0].size(); }

};

#endif // MATH_ABSTRACTS_H
