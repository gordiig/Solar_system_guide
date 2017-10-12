#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>

class BaseErr// : public std::exception
{
protected:
    std::string where;

public:
    BaseErr(const char *where) : where(where) { }
    virtual ~BaseErr() { where.clear(); }
    virtual const char* what() const { return "\nUnknown Error!"; }
};

class FileOpeningErr : public BaseErr
{
public:
    FileOpeningErr(const char *where) : BaseErr(where) { }
    const char* what() const;
};

class FileOpenErr : public BaseErr
{
public:
    FileOpenErr(const char *where) : BaseErr(where) { }
    const char* what() const;
};

class VecRangeErr : public BaseErr
{
public:
    VecRangeErr(const char *where) : BaseErr(where) { }
    const char* what() const;
};

class ColorIntenseErr : public BaseErr
{
public:
    ColorIntenseErr(const char *where) : BaseErr(where) { }
    const char* what() const;
};

class MatSizeErr : public BaseErr
{
public:
    MatSizeErr(const char *where) : BaseErr(where) { }
    const char* what() const;
};

class NotEnoughPointsForPoly : public BaseErr
{
public:
    NotEnoughPointsForPoly(const char *where) : BaseErr(where) { }
    const char* what() const;
};

#endif // ERRORS_H
