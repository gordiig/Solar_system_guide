#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include "obj.h"
#include "err.h"

class Logger
{
private:
    std::ofstream log_file;

public:
    Logger() { }
    Logger(const char *name);
    ~Logger();

    void openLogFile(const char *name);
    void closeLogFile();
    bool isOpened();
};

#endif // LOGGER_H
