#ifndef READER_H
#define READER_H

#include <fstream>
#include <vector>
#include <string.h>
#include "obj.h"
#include "errors.h"
#include "logger.h"


class Reader
{
protected:
    std::ifstream file;
    std::vector<Dot3D<double>> read_dots();
    std::vector<std::list<int>> read_poly();

public:
    Reader() {}
    Reader(const char*);
    ~Reader();

    void openFile(const char*);
    void closeFile();
    void resetFile();

    Obj read();
    Obj read(const char*);
};


#endif // READER_H
