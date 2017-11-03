#include "errors.h"

const char* FileOpenErr::what() const
{
    return std::string(std::string("\nERROR\nFile is not opened!") + where).c_str();
}

const char* FileOpeningErr::what() const
{
    return std::string(std::string("\nERROR\nError with reading file!") + where).c_str();
}

const char* VecRangeErr::what() const
{
    return std::string(std::string("\nERROR\nVector range error!") + where).c_str();
}

const char* ColorIntenseErr::what() const
{
    return std::string(std::string("\nERROR\nColor intensive error!") + where).c_str();
}

const char* MatSizeErr::what() const
{
    return std::string(std::string("\nERROR\nMatrix size error!") + where).c_str();
}

const char* NotEnoughPointsForPoly::what() const
{
    return std::string(std::string("\nERROR\nNot enough dots for make polygon!") + where).c_str();
}

const char* ImgOpenErr::what() const
{
    return std::string(std::string("\nERROR\nError with opening the image !") + where).c_str();
}
